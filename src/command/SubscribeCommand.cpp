//
// Created by Ivan Kishchenko on 26.12.2020.
//

#include <message/SubscribeMessage.h>
#include <message/SubAckMessage.h>
#include <event/Event.h>
#include "SubscribeCommand.h"


namespace mqtt {

    void SubscribeCommand::execute(const std::function<void(const ErrorCode &)> &callback) {
        auto msg = std::make_shared<message::SubscribeMessage>();
        msg->addTopic(_topic, _qos);
        Client::Ptr client = _client;

        client->post(msg).then([msg, client, callback](ErrorFuture future) {
            auto err = future.get();
            if (!err) {
                client->getEventManager()->subscribe<EventChannelMessage>([msg, client, callback](const EventChannelMessage &event) -> bool {
                    auto *ack = dynamic_cast<message::SubAckMessage *>(event.getMessage().get());
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