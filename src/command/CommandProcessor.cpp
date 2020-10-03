//
// Created by Kishchenko, Ivan on 9/30/20.
//

#include <boost/asio/post.hpp>
#include "CommandProcessor.h"

using namespace boost;

namespace mqtt::command {

    CommandProcessor::CommandProcessor(boost::asio::io_service &service) : _service(service) {}

    void CommandProcessor::execute(const Command::Ptr& command) {
        asio::post(_service, [this,command]() {
            this->doCommand(command);
        })
    }

    void CommandProcessor::doCommand(Command::Ptr command) {
        uint64_t id = command->execute();
        if (command->hasReply()) {
            _waiting[id] = command;
        }
    }


}