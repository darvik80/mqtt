//
// Created by Ivan Kishchenko on 26.12.2020.
//

#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include "UserStd.h"
#include "event/EventManager.h"

namespace mqtt {

    class Subscription;
    class Publisher;

    class Client {
    public:
        typedef std::shared_ptr<Client> Ptr;
        typedef std::weak_ptr<Client> WeakPtr;
    public:
        virtual VoidFuture post(const message::Message::Ptr &msg) = 0;

        virtual Subscription subscribe(std::string_view topic, uint8_t qos, const DataCallback &&callback) = 0;

        virtual Publisher publisher(std::string_view topic, uint8_t qos) = 0;

        virtual EventManager::Ptr getEventManager() = 0;

        virtual uint16_t getPacketIdentifier() = 0;

        virtual ~Client() = default;
    };

}


#endif //MQTT_CLIENT_H
