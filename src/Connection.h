//
// Created by Ivan Kishchenko on 19.09.2020.
//

#ifndef MQTT_CONNECTION_H
#define MQTT_CONNECTION_H

#include "properties/ConnectionProperties.h"

#include <map>
#include "Encoder.h"
#include "Decoder.h"
#include "Timer.h"
#include "Future.h"
#include <boost/signals2.hpp>
#include "EventManager.h"

namespace mqtt {

    enum ConnectionStatus {
        IDLE,
        ACTIVE,
        CONNECTED,
    };

    class MqttConnection {
    public:
        virtual void post(const message::Message::Ptr& msg, FutureListenerErrorCode listene) = 0;
        //virtual FutureErrorCode post(const message::Message::Ptr& msg) = 0;
        virtual void onMessage(const message::Message::Ptr& msg) = 0;
    };

    class Connection : public MqttConnection, Component {
    private:
        properties::ConnectionProperties _props;

        ConnectionStatus _status{IDLE};
        TcpEndpoint _endpoint;
        TcpSocket _socket;

        ByteBuffer _incBuf;
        boost::asio::streambuf _inc;
        boost::asio::streambuf _out;

        Encoder _encoder;
        Decoder _decoder;

        uint16_t _packetIdentifier{0};

        Timer::AutoPtr _timer;

        EventManager _eventManager;
    private:
        void startConnect();
        void startRead();

        void channelActive();

        void channelInactive(const ErrorCode &err);

        void channelReadComplete(const ErrorCode &err, size_t readSize);

        void channelWriteComplete(const ErrorCode &err, size_t writeSize);
    public:
        explicit Connection(const properties::ConnectionProperties &props);
        void post(const message::Message::Ptr& msg, FutureListenerErrorCode listener) override;
        //void post(const message::Message::Ptr& msg, PromiseErrorCode& promise) override;
        void onMessage(const message::Message::Ptr& msg) override;
    public: // Getters
        EventManager &getEventManager();
    };
}


#endif //MQTT_CONNECTION_H
