//
// Created by Ivan Kishchenko on 20.12.2020.
//

#ifndef MQTT_EVENT_H
#define MQTT_EVENT_H

#include "message/Message.h"
#include "UserStd.h"

namespace mqtt {

    class Connection;

    class Event {
    private:
        const Connection &_connection;

    public:
        explicit Event(const Connection &connection)
                : _connection(connection) {}

        const Connection &getConnection() {
            return _connection;
        }
    };

    class EventChannelActive : public Event {
    public:
        explicit EventChannelActive(const Connection &connection)
                : Event(connection) {}
    };


    class EventChannelInactive : public Event {
    private:
        const ErrorCode _err;
    public:
        EventChannelInactive(const Connection &connection, const ErrorCode &err)
                : Event(connection), _err(err) {}

        const ErrorCode &getErr() const {
            return _err;
        }
    };

    class EventChannelMessage : public Event {
    private:
        const message::Message::Ptr _message;
    public:
        EventChannelMessage(const Connection &connection, const message::Message::Ptr &message)
                : Event(connection), _message(message) {}

        const message::Message::Ptr &getMessage() const {
            return _message;
        }
    };
}

#endif //MQTT_EVENT_H
