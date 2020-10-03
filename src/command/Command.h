//
// Created by Kishchenko, Ivan on 9/30/20.
//

#ifndef MQTT_COMMAND_H
#define MQTT_COMMAND_H

#include <memory>

namespace mqtt::command {

    class Command {
    public:
        typedef std::shared_ptr<Command> Ptr;
    public:
        virtual bool hasReply() = 0;

        virtual uint64_t execute() = 0;
    };
}

#endif //MQTT_COMMAND_H
