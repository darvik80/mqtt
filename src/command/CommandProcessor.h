//
// Created by Kishchenko, Ivan on 9/30/20.
//

#ifndef MQTT_COMMANDPROCESSOR_H
#define MQTT_COMMANDPROCESSOR_H

#include <boost/asio/io_service.hpp>
#include "Command.h"

namespace mqtt::command {

    class CommandProcessor {
    private:
        boost::asio::io_service& _service;
        std::map<uint64_t, Command::Ptr> _waiting;
    private:
        void doCommand(Command::Ptr command);
    public:
        CommandProcessor(boost::asio::io_service &service);

        void execute(const Command::Ptr& command);
    };

}


#endif //MQTT_COMMANDPROCESSOR_H
