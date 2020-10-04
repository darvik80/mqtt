//
// Created by Ivan Kishchenko on 19.09.2020.
//

#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio.hpp>

#include <memory>
#include <map>
#include "Encoder.h"
#include "Decoder.h"
#include "Timer.h"
#include "Future.h"
#include "Channel.h"
#include "ChannelPipeline.h"

namespace mqtt {

    struct ClientProperties {
        std::string address;
        int port;
    };

    enum ConnectionStatus {
        IDLE,
        ACTIVE,
        CONNECTED,
    };

    class Client : public Channel, public ChannelInboundHandler, public ChannelOutboundHandler {
    private:
        ConnectionStatus _status{IDLE};
        boost::asio::io_service &_service;
        boost::asio::ip::tcp::endpoint _endpoint;
        boost::asio::ip::tcp::socket _socket;

        std::vector<uint8_t> _incBuf;
        boost::asio::streambuf _inc;
        boost::asio::streambuf _out;

        Timer::AutoPtr _restartTimer;
        Encoder _encoder;
        Decoder _decoder;

        ChannelPipeline _pipeline;

        uint16_t _packetIdentifier{0};
    private:
        void startConnect();

        void startRead();

        bool checkError(ChannelContext &ctx);

    public:
        Client(boost::asio::io_service &service, const ClientProperties &props);

        ChannelPipeline& getPipeline() {
            return _pipeline;
        }

        void channelActive(ChannelContext &ctx) override;

        void channelInactive(ChannelContext &ctx) override;

        void channelReadComplete(ChannelContext &ctx) override;

        void channelWriteComplete(ChannelContext &ctx) override;

        void onMessage(ChannelContext &ctx, const message::Message::Ptr& msg) override;
    public:
        void write(const message::Message::Ptr& msg, FutureListenerErrorCode listener) override;
    };
}


#endif //MQTT_CLIENT_H
