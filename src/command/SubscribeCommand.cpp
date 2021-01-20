//
// Created by Ivan Kishchenko on 26.12.2020.
//

#include <message/SubscribeMessage.h>
#include <message/SubAckMessage.h>
#include <event/EventNetwork.h>

#include <memory>
#include "SubscribeCommand.h"

namespace mqtt {

    using namespace mqtt::message;

    boost::future<void> SubscribeCommand::execute() {
        auto promise = std::make_shared<boost::promise<void>>();
        auto msg = std::make_shared<SubscribeMessage>(_topic, _qos, getPacketIdentifier());

        request<SubscribeMessage, SubAckMessage>(msg).then([promise](boost::future<SubAckMessage> ack) {
            try {
                if (ack.get().getReturnCode() > 2) {
                    promise->set_exception(boost::system::system_error(boost::asio::error::operation_aborted));
                } else {
                    promise->set_value();
                }
            } catch (boost::system::system_error& ex) {
                promise->set_exception(ack.get_exception_ptr());
            }
        });

        return promise->get_future();
    }
}