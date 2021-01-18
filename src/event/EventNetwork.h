//
// Created by Ivan Kishchenko on 26.12.2020.
//

#ifndef MQTT_EVENTNETWORK_H
#define MQTT_EVENTNETWORK_H

#include "Event.h"

namespace mqtt {

    class Connection;

    class EventNetwork : public Event {
        const Connection &_connection;
    public:
        explicit EventNetwork(const ErrorCode &err, const Connection &connection)
                : Event(err), _connection(connection) {}
        explicit EventNetwork(const Connection &connection)
                : _connection(connection) {}


        const Connection &getConnection() {
            return _connection;
        }
    };

    class EventChannelActive : public EventNetwork {
    public:
        explicit EventChannelActive(const Connection &connection)
                : EventNetwork(connection) {}
    };

    class EventChannelInactive : public EventNetwork {
    public:
        EventChannelInactive(const Connection &connection, const ErrorCode &err)
                : EventNetwork(err, connection) {}
    };

    class EventChannelMessage : public EventNetwork {
    private:
        const message::Message::Ptr _message;
    public:
        EventChannelMessage(const Connection &connection, const message::Message::Ptr &message)
                : EventNetwork(connection), _message(message) {}

        [[nodiscard]] const message::Message::Ptr &getMessage() const {
            return _message;
        }
    };

}

#endif //MQTT_EVENTNETWORK_H
