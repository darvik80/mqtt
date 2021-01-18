//
// Created by Ivan Kishchenko on 24.12.2020.
//

#ifndef MQTT_SUBSCRIBER_H
#define MQTT_SUBSCRIBER_H

#include "UserStd.h"

#include "Client.h"
#include "Command.h"

#include "event/EventHandler.h"
#include "event/EventNetwork.h"

#include <command/SubscribeCommand.h>
#include <command/UnSubscribeCommand.h>

#include <message/PublishMessage.h>
#include "logging/Logger.h"
#include "TopicFilter.h"

namespace mqtt {
    class Subscriber : public EventChannelMessageHandler, public EventChannelActiveHandler, public std::enable_shared_from_this<Subscriber> {
    public:
        typedef std::shared_ptr<Subscriber> Ptr;
        typedef std::weak_ptr<Subscriber> WeakPtr;
    private:
        std::mutex _lock;

        const std::function<void(const ByteBuffer &)> _callback;
        Command::Ptr _cmdSubscribe;
        Command::Ptr _cmdUnSubscribe;

        Client::WeakPtr _client;

        TopicFilter _filter;
    public:
        Subscriber(Client::Ptr client, std::string_view topic, uint8_t qos, const std::function<void(const ByteBuffer &)> &callback)
                : _callback(callback), _client(client), _filter(topic) {
            _cmdSubscribe = std::make_shared<SubscribeCommand>(client, topic, qos);
            _cmdUnSubscribe = std::make_shared<UnSubscribeCommand>(client, topic);
        }

        void onEvent(const EventChannelMessage &event) override {
            auto pub = dynamic_cast<message::PublishMessage *>(event.getMessage().get());
            if (pub && _callback) {
                if (_filter.filter(pub->getTopic())) {
                    _callback(pub->getMessage());
                }
            }
        }

        void onEvent(const EventChannelActive &event) override {
            start();
        }

        void start() {
            std::lock_guard guard(_lock);
            if (_cmdSubscribe) {
                _cmdSubscribe->execute([this](const ErrorCode &err) {
                    if (err) {
                        MQTT_LOG(info) << "Can't subscribe to: " << _filter.getFilter() << ", error: " << err.message();
                    }

                    if (!_cmdSubscribe) {
                        shutdown();
                    }
                });
            }
        }

        void shutdown() {
            std::lock_guard guard(_lock);
            _cmdSubscribe.reset();
            _cmdUnSubscribe->execute([this](const ErrorCode &err) {
                if (err) {
                    MQTT_LOG(info) << "Can't unSubscribe to: " << _filter.getFilter() << ", error: " << err.message();
                }
            });

            auto client = _client.lock();
            if (client) {
                client->getEventManager()->raiseEvent(EventTopicUnSubscribe{shared_from_this(), _filter.getFilter()});
            }
        }

        ~Subscriber() override {
            MQTT_LOG(info) << "Subscriber: " << _filter.getFilter() << " destroyed";
        }
    };


    class Subscription {
        Subscriber::WeakPtr _subscriber;
    public:
        explicit Subscription(const Subscriber::Ptr &subscriber)
                : _subscriber(subscriber) {
        }

        explicit Subscription(const Subscriber::WeakPtr &origin)
                : _subscriber(origin) {
        }

        Subscription(const Subscription &other)
                : _subscriber(other._subscriber) {

        }


        Subscription &operator=(const Subscription &other) {
            if (&other == this) {
                return *this;
            }
            _subscriber = other._subscriber;
            return *this;
        }

    public: //control
        bool start() {
            Subscriber::Ptr ptr = _subscriber.lock();
            if (ptr) {
                ptr->start();
            }

            return ptr != nullptr;
        }

        bool shutdown() const {
            Subscriber::Ptr ptr = _subscriber.lock();
            if (ptr) {
                ptr->shutdown();
            }

            return ptr != nullptr;
        }
    };
}


#endif //MQTT_SUBSCRIBER_H
