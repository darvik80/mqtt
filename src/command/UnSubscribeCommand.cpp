//
// Created by Ivan Kishchenko on 26.12.2020.
//

#include <message/UnSubscribeMessage.h>
#include <message/UnSubAckMessage.h>
#include "UnSubscribeCommand.h"

namespace mqtt {
    UnSubscribeCommand::UnSubscribeCommand(const Client::Ptr &client, const std::string_view topic)
            : _client(client), _topic(topic) {}

    void UnSubscribeCommand::execute(const std::function<void(const ErrorCode &)> &callback) {
        auto msg = std::make_shared<message::UnSubscribeMessage>();
        msg->addTopicFilter(_topic);
        Client::Ptr client = _client;
        client->post(msg).then([=](ErrorFuture future) {
            auto err = future.get();
            if (!err) {
                client->getEventManager()->subscribe<EventChannelMessage>([=](const EventChannelMessage &event) -> bool {
                    auto *ack = dynamic_cast<message::UnSubAckMessage *>(event.getMessage().get());
                    if (ack && ack->getPacketIdentifier() == msg->getPacketIdentifier()) {
                        callback(ErrorCode{});
                        return false; // disconnect from event
                    }

                    return true; // continue receive events
                });

            } else {
                callback(err);
            }
        });
    }

}

