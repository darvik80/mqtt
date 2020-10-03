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

namespace mqtt {

    class SubscribeCallback {
    public:
        typedef std::shared_ptr<SubscribeCallback> Ptr;
    public:
        virtual void onData(const std::vector<uint8_t> &data) = 0;
    };

    struct ClientProperties {
        std::string address;
        int port;
    };


    typedef void (*FutureListener)(const Future &future);

    enum ConnectionStatus {
        IDLE,
        ACTIVE,
        CONNECTED,
    };

    class Client : public ChannelInboundHandler {
    private:
        ConnectionStatus _status{IDLE};
        boost::asio::io_service &_service;
        boost::asio::ip::tcp::endpoint _endpoint;
        boost::asio::ip::tcp::socket _socket;

        std::vector<uint8_t> _incBuf;
        boost::asio::streambuf _inc;
        boost::asio::streambuf _out;

        Timer::AutoPtr _restartTimer;
        Timer::AutoPtr _pingTimer;

        Encoder _encoder;
        Decoder _decoder;
    private:
        void onRead(const boost::system::error_code &err, std::size_t size);

        void onWrite(const boost::system::error_code &err, std::size_t size);

        void startConnect();

        void startRead();

        void heartBeat();

        bool checkError(const boost::system::error_code &err);

        void onMessage(message::Message::Ptr msg);

    public:
        Client(boost::asio::io_service &service, const ClientProperties &props);

        void send(message::Message::Ptr msg, FutureListener listener);

        void post(message::Message::Ptr msg);

        void channelActive(ChannelContext &ctx) override;

        void channelInactive(ChannelContext &ctx) override;

        void channelReadComplete(ChannelContext &ctx) override;
    };
}


#endif //MQTT_CLIENT_H
