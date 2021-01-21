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
#include <boost/signals2.hpp>
#include "event/EventManager.h"

namespace mqtt {

    enum ConnectionStatus {
        IDLE,
        ACTIVE,
        CONNECTED,
    };

    class Connection {
    public:
        typedef std::shared_ptr<Connection> Ptr;
        typedef std::weak_ptr<Connection> WeakPtr;
    public:
        Connection() = default;

        virtual VoidFuture post(const message::Message::Ptr &msg) = 0;

        virtual void onMessage(const message::Message::Ptr &msg) = 0;

        virtual ~Connection() = default;
    };

    class DefaultConnection : public Connection, Component {
    private:
        properties::ConnectionProperties _props;

        mutable ConnectionStatus _status{IDLE};
        TcpEndpoint _endpoint;
        TcpSocket _socket;

        ByteBuffer _incBuf;
        boost::asio::streambuf _inc;
        boost::asio::streambuf _out;

        Encoder _encoder;
        Decoder _decoder;

        uint16_t _packetIdentifier{0};

        Timer::Ptr _timer;

        EventManager::Ptr _eventManager;

        PosixTime _lastUpdate;
        bool _shutdown{false};
    private:
        void startConnect();

        void startRead();

        void channelActive();

        void channelInactive(const ErrorCode &err);

        void channelReadComplete(const ErrorCode &err, size_t readSize);

        void channelWriteComplete(const ErrorCode &err, size_t writeSize);

        template<class T>
        void raiseEvent(const T &event) {
            if (_eventManager) {
                _eventManager->raiseEvent(event);
            }
        }

    public:
        explicit DefaultConnection(const properties::ConnectionProperties &props);

        VoidFuture post(const message::Message::Ptr &msg) override;

        void onMessage(const message::Message::Ptr &msg) override;

    public:
        void start();

        void stop();

        void setEventManager(EventManager::Ptr eventManager);
    };
}


#endif //MQTT_CONNECTION_H
