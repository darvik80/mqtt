//
// Created by Ivan Kishchenko on 20.12.2020.
//

#ifndef MQTT_EVENT_H
#define MQTT_EVENT_H

#include "message/Message.h"
#include "UserStd.h"

namespace mqtt {

    class Connection;

    enum EventType {
        EVENT_CHANNEL_ACTIVE,
        EVENT_CHANNEL_INACTIVE,
        EVENT_CHANNEL_MESSAGE,
    };

    class Event {
    private:
        uint16_t _eventType;
        const Connection &_connection;

    public:
        explicit Event(uint16_t eventType, const Connection &connection)
                : _eventType(eventType), _connection(connection) {}

        const Connection &getConnection() {
            return _connection;
        }

        [[nodiscard]] uint16_t getEventType() const {
            return _eventType;
        }

        virtual ~Event() = default;
    };

    class EventChannelActive : public Event {
    public:
        explicit EventChannelActive(const Connection &connection)
                : Event(EVENT_CHANNEL_ACTIVE, connection) {}
    };


    class EventChannelInactive : public Event {
    private:
        const ErrorCode _err;
    public:
        EventChannelInactive(const Connection &connection, const ErrorCode &err)
                : Event(EVENT_CHANNEL_INACTIVE, connection), _err(err) {}

        [[nodiscard]] const ErrorCode &getErr() const {
            return _err;
        }
    };

    class EventChannelMessage : public Event {
    private:
        const message::Message::Ptr _message;
    public:
        EventChannelMessage(const Connection &connection, const message::Message::Ptr &message)
                : Event(EVENT_CHANNEL_MESSAGE, connection), _message(message) {}

        [[nodiscard]] const message::Message::Ptr &getMessage() const {
            return _message;
        }
    };
}

#endif //MQTT_EVENT_H
