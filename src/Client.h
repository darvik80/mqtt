//
// Created by Ivan Kishchenko on 19.09.2020.
//

#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include "properties/ClientProperties.h"

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

    enum ConnectionStatus {
        IDLE,
        ACTIVE,
        CONNECTED,
    };

    class MqttClient {
    public:
        virtual void post(const message::Message::Ptr& msg, FutureListenerErrorCode listene) = 0;
        virtual void onMessage(const message::Message::Ptr& msg) = 0;
    };

    class Client : public MqttClient {
    private:
        properties::ClientProperties _props;

        ConnectionStatus _status{IDLE};
        IoService &_service;
        TcpEndpoint _endpoint;
        TcpSocket _socket;

        ByteBuffer _incBuf;
        boost::asio::streambuf _inc;
        boost::asio::streambuf _out;

        Timer::AutoPtr _restartTimer;
        Encoder _encoder;
        Decoder _decoder;

        uint16_t _packetIdentifier{0};
    private:
        void startConnect();
        void startRead();

    public:
        Client(boost::asio::io_service &service, const properties::ClientProperties &props);

        void channelActive();

        void channelInactive(const ErrorCode &err);

        void channelReadComplete(const ErrorCode &err, size_t readSize);

        void channelWriteComplete(const ErrorCode &err, size_t writeSize);
    public:
        void post(const message::Message::Ptr& msg, FutureListenerErrorCode listener) override;
        void onMessage(const message::Message::Ptr& msg) override;
    };
}


#endif //MQTT_CLIENT_H
