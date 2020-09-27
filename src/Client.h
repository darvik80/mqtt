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
#include <exception/Exception.h>
#include "Encoder.h"
#include "Decoder.h"
#include "Timer.h"

namespace mqtt {
    class Future {
    public:
        virtual bool isDone() const = 0;
        virtual bool isSuccess() const = 0;
        virtual bool isCancelled() const = 0;
        virtual exception::Exception::Ptr cause() const = 0;
    };

    class SystemFuture : public Future {
    private:
        exception::Exception::Ptr _exception;

    public:
        explicit SystemFuture(const boost::system::error_code &errorCode) {}

        [[nodiscard]] bool isDone() const override {
            return true;
        }

        [[nodiscard]] bool isSuccess() const override {
            return _exception == nullptr;
        }

        [[nodiscard]] bool isCancelled() const override {
            return false;
        }

        [[nodiscard]] exception::Exception::Ptr cause() const override {
            return _exception;
        }
    };

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


    typedef void (*FutureListener)(const Future& future);

    enum ConnectionStatus {
        IDLE,
        ACTIVE,
        CONNECTED,
    };

    class Client {
    private:
        ConnectionStatus _status{IDLE};
        boost::asio::io_service &_service;
        boost::asio::ip::tcp::endpoint _endpoint;
        boost::asio::ip::tcp::socket _socket;

        uint64_t _callbackIdSeq{0};
        std::map<uint64_t, SubscribeCallback::Ptr> _callbacks;

        Encoder _encoder;
        Decoder _decoder;

        std::vector<uint8_t> _incBuf;
        boost::asio::streambuf _inc;
        boost::asio::streambuf _out;

        Timer::AutoPtr _restartTimer;
        Timer::AutoPtr _pingTimer;
    private:
        void onConnect(const boost::system::error_code &err);
        void onRead(const boost::system::error_code& err, std::size_t size);
        void onWrite(const boost::system::error_code& err, std::size_t size);

        void startConnect();
        void startRead();
        void heartBeat();
        bool checkError(const boost::system::error_code& err);
        void send(message::Message::Ptr msg, FutureListener listener);
        void post(message::Message::Ptr msg);
        void onMessage(message::Message::Ptr msg);
    public:
        Client(boost::asio::io_service &service, const ClientProperties &props);

        void subscribe(const std::string &topicFilter, int qos, SubscribeCallback::Ptr callback);
    };

}


#endif //MQTT_CLIENT_H
