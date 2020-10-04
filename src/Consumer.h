//
// Created by Ivan Kishchenko on 04.10.2020.
//

#ifndef MQTT_CONSUMER_H
#define MQTT_CONSUMER_H

#include <string>
#include <message/Message.h>
#include "Client.h"


namespace mqtt {
    typedef std::function<uint32_t(const message::PublishMessage *msg)> ConsumerCallback;

    class Consumer {
    public:
        virtual void subscribe(const std::string &topicFilter, uint8_t qos, ConsumerCallback callback) = 0;
    };


    class DefaultConsumer : public Consumer, public ChannelInboundHandler {
    private:
        std::shared_ptr<message::SubscribeMessage> _subscribe;

        ConsumerCallback _callback;
    public:
        DefaultConsumer() = default;

        void subscribe(const std::string &topicFilter, uint8_t qos, ConsumerCallback callback) override;

        void channelActive(ChannelContext &ctx) override;

        void channelInactive(ChannelContext &ctx) override;

        void channelReadComplete(ChannelContext &ctx) override;

        void onMessage(ChannelContext &ctx, const message::Message::Ptr& message) override;
    };
}


#endif //MQTT_CONSUMER_H
