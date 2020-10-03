//
// Created by Kishchenko, Ivan on 9/30/20.
//

#ifndef MQTT_CHANNEL_H
#define MQTT_CHANNEL_H

#include <boost/asio.hpp>
#include "Future.h"

namespace mqtt {

    class ChannelContext {
    public:
        virtual boost::asio::io_service& getIoService() = 0;
        virtual boost::asio::ip::tcp::socket& getSocket() = 0;
        virtual const boost::system::error_code& getErrorCode() = 0;
        virtual std::size_t getSize() = 0;
    };

    class DefaultChannelContext : public ChannelContext {
    private:
        boost::asio::io_service& _service;
        boost::asio::ip::tcp::socket& _socket;
        const boost::system::error_code& _errorCode;
        std::size_t _size;
    public:
        DefaultChannelContext(boost::asio::io_service &service, boost::asio::ip::tcp::socket &socket,
                              const boost::system::error_code &errorCode, size_t size) : _service(service), _socket(socket),
                                                                                   _errorCode(errorCode), _size(size) {}

        boost::asio::io_service &getIoService() override {
            return _service;
        }

        boost::asio::ip::tcp::socket &getSocket() override {
            return _socket;
        }

        const boost::system::error_code &getErrorCode() override {
            return _errorCode;
        }

        std::size_t getSize() override {
            return _size;
        }
    };

    class ChannelInboundHandler {
    public:
        virtual void channelActive(ChannelContext& ctx) = 0;
        virtual void channelInactive(ChannelContext& ctx) = 0;
        virtual void channelReadComplete(ChannelContext& ctx) = 0;
    };

    template<typename T>
    class ChannelOutboundHandler {
    public:
        virtual void write(ChannelContext& ctx, T msg, Future future) = 0;
    };

}


#endif //MQTT_CHANNEL_H
