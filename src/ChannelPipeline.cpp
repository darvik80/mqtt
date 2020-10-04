//
// Created by Ivan Kishchenko on 03.10.2020.
//

#include "ChannelPipeline.h"

namespace mqtt {

    void ChannelPipeline::addLast(const std::string &name, const ChannelHandler::Ptr& handler) {
        _handlers.emplace_back(name, handler);
    }

    void ChannelPipeline::addFirst(const std::string &name, const ChannelHandler::Ptr& handler) {
        _handlers.push_front(std::pair{name, handler});
    }

    void ChannelPipeline::channelActive(ChannelContext &ctx) {
        for (auto &handler : getInboundHandlers()) {
            handler->channelActive(ctx);
        }
    }

    void ChannelPipeline::channelInactive(ChannelContext &ctx) {
        for (auto &handler : getInboundHandlers()) {
            handler->channelInactive(ctx);
        }
    }

    void ChannelPipeline::channelReadComplete(ChannelContext &ctx) {
        for (auto &handler : getInboundHandlers()) {
            handler->channelReadComplete(ctx);
        }
    }

    void ChannelPipeline::onMessage(ChannelContext &ctx, const message::Message::Ptr& message) {
        for (auto &handler : getInboundHandlers()) {
            handler->onMessage(ctx, message);
        }
    }

    void ChannelPipeline::channelWriteComplete(ChannelContext &ctx) {
        for (auto &handler : getOutboundHandlers()) {
            handler->channelWriteComplete(ctx);
        }
    }

    std::vector<ChannelInboundHandler *> ChannelPipeline::getInboundHandlers() {
        std::vector<ChannelInboundHandler *> inbound;
        for (auto &handler : _handlers) {
            auto *h = dynamic_cast<ChannelInboundHandler *>(handler.second.get());
            if (h != nullptr) {
                inbound.push_back(h);
            }
        }

        return inbound;
    }

    std::vector<ChannelOutboundHandler *> ChannelPipeline::getOutboundHandlers() {
        std::vector<ChannelOutboundHandler *> outbound;
        for (auto &handler : _handlers) {
            auto *h = dynamic_cast<ChannelOutboundHandler *>(handler.second.get());
            if (h != nullptr) {
                outbound.push_back(h);
            }
        }

        return outbound;
    }
}