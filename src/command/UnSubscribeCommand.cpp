//
// Created by Ivan Kishchenko on 26.12.2020.
//

#include <message/UnSubscribeMessage.h>
#include <message/UnSubAckMessage.h>
#include "UnSubscribeCommand.h"

namespace mqtt {
    UnSubscribeCommand::UnSubscribeCommand(const Client::Ptr &client, const std::string_view topic)
            : Command(client), _topic(topic) {}

    using namespace mqtt::message;

    boost::future<void> UnSubscribeCommand::execute() {
        auto promise = std::make_shared<boost::promise<void>>();
        auto msg = std::make_shared<UnSubscribeMessage>(_topic, getPacketIdentifier());

        request<UnSubscribeMessage, UnSubAckMessage>(msg).then([promise](boost::future<message::UnSubAckMessage> ack) {
            try {
                ack.get();
                promise->set_value();
            } catch (boost::system::system_error &ex) {
                promise->set_exception(ack.get_exception_ptr());
            }
        });

        return promise->get_future();
    }
}

