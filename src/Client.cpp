//
// Created by Ivan Kishchenko on 19.09.2020.
//

#include "Client.h"

#include <utility>
#include "logging/Logger.h"

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
            if (!_socket.is_open() || err) {
                if (!_socket.is_open()) {
                    MQTT_LOG(info) << "Connect timed out";
                } else {
                    MQTT_LOG(info) << "Connect error: " << err.message();
                    _socket.close();
                }

                _restartTimer = std::make_unique<Timer>(_service, 10, [this]() { this->startConnect(); });
            } else {
                MQTT_LOG(info) << "Connected!";
                _status = ACTIVE;

                startRead();

                DefaultChannelContext ctx(_service, *this, err, 0);
                this->channelActive(ctx);
            }

        });
    }

    void Client::startRead() {
        _socket.async_read_some(
                boost::asio::buffer(_incBuf),
                [this](const boost::system::error_code &err, std::size_t size) {
                    DefaultChannelContext ctx(_service, *this, err, size);
                    this->channelReadComplete(ctx);
                }
        );
    }

    bool Client::checkError(ChannelContext &ctx) {
        if (ctx.getErrorCode().failed()) {
            channelInactive(ctx);
            startConnect();
        }

        return ctx.getErrorCode().failed();
    }

    void Client::onMessage(ChannelContext &ctx, const message::Message::Ptr& msg) {
        MQTT_LOG(info) << "Recv: " << mqttMsgName(msg->getType());
        switch (msg->getType()) {
            case MQTT_MSG_CONNACK: {
                auto ack = (ConnAckMessage *) msg.get();
                if (ack->getReasonCode()) {
                    MQTT_LOG(error) << "Failed: " << ack->getReasonCode();
                } else {
                    _status = CONNECTED;
                    MQTT_LOG(info) << "Connected TO MQTT";
                    _pipeline.channelActive(ctx);
                }
            }
                break;
            case MQTT_MSG_DISCONNECT: {
                _status = IDLE;
                startConnect();
            }
                break;
        }

        _pipeline.onMessage(ctx, msg);
    }

    void Client::channelActive(ChannelContext &ctx) {
        write(std::make_shared<ConnectMessage>("Rover"), nullptr);
    }

    void Client::channelInactive(ChannelContext &ctx) {
        MQTT_LOG(info) << "Disconnected!";
        _pipeline.channelInactive(ctx);
    }

    void Client::channelReadComplete(ChannelContext &ctx) {
        if (ctx.getErrorCode()) {
            MQTT_LOG(info) << "OnRead Failed: " << ctx.getErrorCode().message() << ", " << ctx.getSize();
            asio::dispatch(_service, [this]() { startConnect(); });
            return;
        }

        if (ctx.getSize()) {
            _inc.sputn((const char *) _incBuf.data(), ctx.getSize());

            try {
                while (_inc.size()) {
                    onMessage(ctx, _decoder.decode(_inc));
                }
            } catch (std::exception &ex) {
                // catch segmented messages
            }
        }

        _pipeline.channelReadComplete(ctx);

        startRead();

    }

    void Client::write(const message::Message::Ptr& msg, FutureListenerErrorCode listener) {
        asio::dispatch(_service, [this, msg, listener]() {
            MQTT_LOG(info) << "Send: " << mqttMsgName(msg->getType());

            auto identifier = dynamic_cast<MessagePacketIdentifier*>(msg.get());
            if (identifier) {
                identifier->setPacketIdentifier(++_packetIdentifier);
            }

            _encoder.encode(_out, msg);

            PromiseErrorCode promise;
            async_write(_socket, _out, [this, listener, promise = std::move(promise)](const ErrorCode& errorCode, std::size_t size) mutable {
                DefaultChannelContext ctx(_service, *this, errorCode, size);
                this->channelWriteComplete(ctx);

                if (listener != nullptr) {
                    promise.set_value(errorCode);
                    listener(promise.get_future());
                }
            });
        });
    }

    void Client::channelWriteComplete(ChannelContext &ctx) {
        checkError(ctx);
        _pipeline.channelWriteComplete(ctx);
    }
}