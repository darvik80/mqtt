//
// Created by Ivan Kishchenko on 04.10.2020.
//

#include "Consumer.h"
#include "logging/Logger.h"

namespace mqtt {
    void DefaultConsumer::subscribe(const std::string &topicFilter, uint8_t qos, ConsumerCallback callback) {
        _subscribe = std::make_shared<message::SubscribeMessage>();
        _subscribe->addTopic(topicFilter, qos);

        _callback = callback;
    }

    void DefaultConsumer::channelActive(ChannelContext &ctx) {
        if (_subscribe) {
            ctx.getChannel().write(_subscribe, nullptr);
        }
    }

    void DefaultConsumer::channelInactive(ChannelContext &ctx) {

    }

    void DefaultConsumer::channelReadComplete(ChannelContext &ctx) {

    }

    void DefaultConsumer::onMessage(ChannelContext &ctx, const message::Message::Ptr& msg) {
        if (msg->getType() == MQTT_MSG_SUBACK) {
            auto identifier = dynamic_cast<message::MessagePacketIdentifier *> (msg.get());
            if (identifier && identifier->getPacketIdentifier() == _subscribe->getPacketIdentifier()) {
                MQTT_LOG(info) << "Subscribed to: " << _subscribe->getTopics().size();
            }
        }

        if (msg->getType() == MQTT_MSG_PUBLISH) {
            auto pub = dynamic_cast<message::PublishMessage*>(msg.get());
            uint32_t code = _callback(pub);
            if (code == 0) {
                if (pub->getHeader().bits.qos == 1) {
                    auto pubAck = std::make_shared<message::PubAckMessage>();
                    pubAck->setPacketIdentifier(pub->getPacketIdentifier());
                    ctx.getChannel().write(pubAck, nullptr);
                } else if (pub->getHeader().bits.qos == 2) {
                        //TODO: implement support qos: 2
                    }
            }
        }
    }
}