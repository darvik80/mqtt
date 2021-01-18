//
// Created by Ivan Kishchenko on 20.12.2020.
//

#ifndef MQTT_EVENT_H
#define MQTT_EVENT_H

#include "message/Message.h"
#include "UserStd.h"

#include "EventType.h"

namespace mqtt {

    class Event {
    private:
        const ErrorCode _err;

    public:
        explicit Event() = default;

        explicit Event(const ErrorCode &err)
                : _err(err) {}

        [[nodiscard]] const ErrorCode &getErr() const {
            return _err;
        }

        virtual ~Event() = default;
    };
}

#endif //MQTT_EVENT_H
