//
// Created by Ivan Kishchenko on 24.12.2020.
//

#ifndef MQTT_FACTORY_H
#define MQTT_FACTORY_H

#include "properties/ConnectionProperties.h"
#include "Connection.h"

#include "Subscriber.h"
#include "Publisher.h"

namespace mqtt {

    class DefaultClient : public Client, public EventTopicUnSubscribeHandler, public std::enable_shared_from_this<DefaultClient> {
    private:
        Connection::Ptr _connection;
        EventManager::Ptr _eventManager;

        std::unordered_set<Subscriber::Ptr> _subscribers;
    public:
        DefaultClient(const Connection::Ptr &connection, EventManager::Ptr &eventManager);

        ErrorFuture post(const message::Message::Ptr &msg) override;

        Subscription subscribe(std::string_view topic, uint8_t qos, const std::function<void(const ByteBuffer &)>& callback) override;

        Publisher publisher(std::string_view topic, uint8_t qos) override;

        EventManager::Ptr getEventManager() override;

        void onEvent(const EventTopicUnSubscribe &event) override;

        virtual ~DefaultClient();
    };

    class Factory {
    public:
        typedef std::shared_ptr<Factory> Ptr;
    public:
        Client::Ptr create(const properties::ConnectionProperties &props);
    };
}


#endif //MQTT_FACTORY_H
