//
// Created by Kishchenko, Ivan on 9/30/20.
//

#ifndef MQTT_CHANNEL_H
#define MQTT_CHANNEL_H

#include <boost/asio.hpp>
#include "Future.h"
#include "UserStd.h"
#include <memory>
#include <message/Message.h>

namespace mqtt {

    class Channel {
    public:
        virtual void write(const message::Message::Ptr& msg, FutureListenerErrorCode listener) = 0;
    };

    class ChannelContext {
    public:
        virtual boost::asio::io_service &getIoService() = 0;

        virtual Channel &getChannel() = 0;

        virtual const boost::system::error_code &getErrorCode() = 0;

        virtual std::size_t getSize() = 0;
    };

    class DefaultChannelContext : public ChannelContext {
    private:
        boost::asio::io_service &_service;
        Channel &_channel;
        const boost::system::error_code &_errorCode;
        std::size_t _size;
    public:
        DefaultChannelContext(boost::asio::io_service &service, Channel &channel,
                              const boost::system::error_code &errorCode, size_t size) : _service(service),
                                                                                         _channel(channel),
                                                                                         _errorCode(errorCode),
                                                                                         _size(size) {}

        boost::asio::io_service &getIoService() override {
            return _service;
        }

        Channel &getChannel() override {
            return _channel;
        }

        const boost::system::error_code &getErrorCode() override {
            return _errorCode;
        }

        std::size_t getSize() override {
            return _size;
        }
    };

    class ChannelHandler {
    public:
        typedef std::shared_ptr<ChannelHandler> Ptr;

        virtual ~ChannelHandler() = default;
    };

    class ChannelInboundHandler : virtual public ChannelHandler {
    public:
        virtual void channelActive(ChannelContext &ctx) = 0;

        virtual void channelInactive(ChannelContext &ctx) = 0;

        virtual void channelReadComplete(ChannelContext &ctx) = 0;

        virtual void onMessage(ChannelContext &ctx, const message::Message::Ptr& message) = 0;
    };

    class ChannelOutboundHandler : virtual public ChannelHandler {
    public:
        virtual void channelWriteComplete(ChannelContext &ctx) = 0;
    };

}


#endif //MQTT_CHANNEL_H
