//
// Created by Ivan Kishchenko on 03.10.2020.
//

#ifndef MQTT_CHANNELPIPELINE_H
#define MQTT_CHANNELPIPELINE_H

#include "Channel.h"
#include <list>

namespace mqtt {

    class ChannelPipeline : public ChannelInboundHandler, public ChannelOutboundHandler {
    private:
        std::list<std::pair<std::string, ChannelHandler::Ptr>> _handlers;

    private:
        std::vector<ChannelInboundHandler*> getInboundHandlers();
        std::vector<ChannelOutboundHandler*> getOutboundHandlers();
    public:
        void addLast(const std::string& name, const ChannelHandler::Ptr& handler);
        void addFirst(const std::string& name, const ChannelHandler::Ptr& handler);
    public:
        void channelActive(ChannelContext &ctx) override;

        void channelInactive(ChannelContext &ctx) override;

        void channelReadComplete(ChannelContext &ctx) override;

        void channelWriteComplete(ChannelContext &ctx) override;

        void onMessage(ChannelContext &ctx, const message::Message::Ptr& message) override;
    };

}

#endif //MQTT_CHANNELPIPELINE_H
