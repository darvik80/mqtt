//
// Created by Ivan Kishchenko on 03.10.2020.
//

#ifndef MQTT_SESSION_H
#define MQTT_SESSION_H

#include "Channel.h"
#include "message/SubscribeMessage.h"

namespace mqtt {
    class Session : public ChannelInboundHandler {
        std::vector<std::string> _topics;
    public:
        Session(const std::vector<std::string>& topics) : _topics(topics) {}

        void channelActive(ChannelContext &ctx) override {
            auto subs = std::make_shared<message::SubscribeMessage>();

            for (auto& topicFilter : _topics) {
                subs->addTopic(topicFilter, 0);
            }

            //ctx.getChannel().write(subs);
        }

        void channelInactive(ChannelContext &ctx) override {

        }
    };

}


#endif //MQTT_SESSION_H
