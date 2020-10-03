//
// Created by Ivan Kishchenko on 19.09.2020.
//

#include "Client.h"

#include <utility>
#include <iostream>

using namespace boost;
using namespace boost::asio;
using namespace mqtt::message;

namespace mqtt {

    Client::Client(boost::asio::io_service &service, const ClientProperties &props)
            : _service(service), _socket(service), _endpoint(ip::address::from_string(props.address), props.port),
              _incBuf(512) {
        startConnect();
    }

    void Client::startConnect() {
        _socket.async_connect(_endpoint, [this](const boost::system::error_code &err) {
            DefaultChannelContext ctx(_service, _socket, err, 0);
            this->channelActive(ctx);
        });
    }

    void Client::startRead() {
        _socket.async_read_some(
                boost::asio::buffer(_incBuf),
                [this](const boost::system::error_code &err, std::size_t size) {
                    DefaultChannelContext ctx(_service, _socket, err, size);
                    this->channelReadComplete(ctx);
                }
        );
    }

    bool Client::checkError(const system::error_code &err) {
        if (err.failed()) {
            startConnect();
        }

        return err.failed();
    }
    void Client::onWrite(const boost::system::error_code &err, std::size_t size) {
        checkError(err);
    }

    void Client::send(message::Message::Ptr msg, FutureListener listener) {
        _encoder.encode(_out, std::move(msg));

        async_write(_socket, _out, [listener](boost::system::error_code errorCode, std::size_t size) {
            if (listener != nullptr) {
                listener(SystemFuture(errorCode));
            }
        });
    }

    void Client::post(message::Message::Ptr msg) {
        send(std::move(msg), nullptr);
    }

    void Client::onMessage(message::Message::Ptr msg) {
        switch (msg->getType()) {
            case MQTT_MSG_CONNACK: {
                auto ack = (ConnAckMessage *) msg.get();
                if (ack->getReasonCode()) {
                    std::cout << "Failed: " << ack->getReasonCode() << std::endl;
                } else {
                    _status = CONNECTED;
                    std::cout << "Connected TO MQTT" << std::endl;
                    heartBeat();
                }
            }
                break;
            case MQTT_MSG_PINGRESP: {
                std::cout << "Pong MQTT" << std::endl;
                heartBeat();
            }
                break;
            case MQTT_MSG_DISCONNECT: {
                _status = IDLE;
                startConnect();
            }
                break;
        }
    }

    void Client::heartBeat() {
        if (_status != CONNECTED) {
            return;
        }
        _pingTimer = std::make_unique<Timer>(_service, 5, [this]() {
            std::cout << "Ping MQTT" << std::endl;
            post(std::make_shared<PingReqMessage>());
        });
    }

    void Client::channelActive(ChannelContext &ctx) {
        if (!ctx.getSocket().is_open() || ctx.getErrorCode()) {
            if (!_socket.is_open()) {
                std::cout << "Connect timed out\n";
            } else {
                std::cout << "Connect error: " << ctx.getErrorCode().message() << "\n";
                _socket.close();
            }

            _restartTimer = std::make_unique<Timer>(ctx.getIoService(), 10, [this]() { this->startConnect(); });
        } else {
            std::cout << "Connected!" << std::endl;
            _status = ACTIVE;

            auto connMsg = std::make_shared<ConnectMessage>();
            connMsg->setClientId("Rover");
            post(connMsg);

            startRead();
        }
    }

    void Client::channelInactive(ChannelContext &ctx) {

    }

    void Client::channelReadComplete(ChannelContext &ctx) {
        if (ctx.getErrorCode()) {
            std::cout << "OnRead: " << ctx.getErrorCode().message() << std::endl;
            startConnect();
        }
        if (ctx.getSize()) {
            _inc.sputn((const char *) _incBuf.data(), ctx.getSize());

            try {
                while (_inc.size()) {
                    onMessage(_decoder.decode(_inc));
                }
            } catch (std::exception &ex) {
                // catch segmented messages
            }
        }

        startRead();
    }
}