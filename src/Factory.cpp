//
// Created by Ivan Kishchenko on 24.12.2020.
//

#include "Factory.h"

namespace mqtt {

    ErrorFuture DefaultClient::post(const message::Message::Ptr &msg) {
        return _connection->post(msg);
    }

    EventManager::Ptr DefaultClient::getEventManager() {
        return _eventManager;
    }

    void DefaultClient::onEvent(const EventTopicUnSubscribe &event) {
        MQTT_LOG(info) << "MQTT Client remove subscriber: " << event.getTopic();
        _subscribers.erase(event.getSubscriber());
    }

    Subscription DefaultClient::subscribe(std::string_view topic, uint8_t qos, const std::function<void(const ByteBuffer &)> &callback) {
        auto subscriber = std::make_shared<Subscriber>(shared_from_this(), topic, qos, callback);

        _eventManager->subscribe<EventChannelActive>(subscriber);
        _eventManager->subscribe<EventChannelMessage>(subscriber);
        _subscribers.insert(subscriber);

        subscriber->start();
        return Subscription{subscriber};
    }

    Publisher DefaultClient::publisher(std::string_view topic, uint8_t qos) {
        return Publisher{shared_from_this(), topic, qos};
    }

    DefaultClient::~DefaultClient() {
        MQTT_LOG(info) << "MQTT Client destroyed";
    }


    DefaultClient::DefaultClient(const Connection::Ptr &connection, EventManager::Ptr &eventManager)
            : _connection(connection), _eventManager(eventManager) {

    }

    Client::Ptr Factory::create(const properties::ConnectionProperties &props) {
        auto conn = std::make_shared<DefaultConnection>(props);
        auto eventManager = std::make_shared<EventManager>();
        conn->setEventManager(eventManager);
        auto client = std::make_shared<DefaultClient>(conn, eventManager);

        eventManager->subscribe<EventTopicUnSubscribe>(client);

        conn->start();

        return client;
    }

}