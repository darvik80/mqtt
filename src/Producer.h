//
// Created by Ivan Kishchenko on 04.10.2020.
//

#ifndef MQTT_PRODUCER_H
#define MQTT_PRODUCER_H

#include <string>
#include "Client.h"

namespace mqtt {

    class Producer {
    public:
        virtual void publish(const std::string &topic, const std::string &msg) = 0;
    };

    class DefaultProducer : public Producer, public ChannelInboundHandler {
        Client& _client;
    public:
        DefaultProducer(Client &client);

        void publish(const std::string &topic, const std::string &msg) override;

        void channelActive(ChannelContext &ctx) override;

        void channelInactive(ChannelContext &ctx) override;

        void channelReadComplete(ChannelContext &ctx) override;

        void onMessage(ChannelContext &ctx, const message::Message::Ptr &message) override;
    };

}

#endif //MQTT_PRODUCER_H
