//
// Created by Ivan Kishchenko on 25.12.2020.
//

#ifndef MQTT_COMMAND_H
#define MQTT_COMMAND_H

#include "UserStd.h"

namespace mqtt {
    class Command {
    public:
        typedef std::shared_ptr<Command> Ptr;
    public:
        virtual void execute(const std::function<void(const ErrorCode &)> &callback) = 0;
    };
}


#endif //MQTT_COMMAND_H
