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

    Client::Client(boost::asio::io_service &service, const properties::ClientProperties &props)
            : _service(service)
            , _socket(service)
            , _endpoint(ip::address::from_string(props.address), props.port)
            , _incBuf(512)
            , _props(props)
    {
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

                this->channelActive();
            }

        });
    }

    void Client::startRead() {
        _socket.async_read_some(
                boost::asio::buffer(_incBuf),
                [this](const boost::system::error_code &err, std::size_t size) {
                    this->channelReadComplete(err, size);
                }
        );
    }

    void Client::onMessage(const message::Message::Ptr& msg) {
        MQTT_LOG(info) << "Recv: " << mqttMsgName(msg->getType());
        switch (msg->getType()) {
            case MQTT_MSG_CONNACK: {
                auto ack = (ConnAckMessage *) msg.get();
                if (ack->getReasonCode()) {
                    MQTT_LOG(error) << "Failed: " << ack->getReasonCode();
                } else {
                    _status = CONNECTED;
                    MQTT_LOG(info) << "Connected TO MQTT";
                }
            }
                break;
            case MQTT_MSG_DISCONNECT: {
                _status = IDLE;
                startConnect();
            }
                break;
        }

    }

    void Client::channelActive() {
        MQTT_LOG(info) << "Channel Active: " << _props.address << ":" << _props.port;
        post(std::make_shared<ConnectMessage>("Rover"), nullptr);
    }

    void Client::channelInactive(const ErrorCode &err) {
        if (err) {
            MQTT_LOG(error) << "Channel inactive: " << _props.address << ":" << _props.port << ", " << err.message();
        } else {
            MQTT_LOG(info) << "Channel inactive: " << _props.address << ":" << _props.port;
        }
    }

    void Client::channelReadComplete(const ErrorCode &err, size_t readSize) {
        if (err) {
            MQTT_LOG(warning) << "Read Failed: " << _props.address << ":" << _props.port <<  ", " << err.message();
            asio::dispatch(_service, [this, err]() {
                channelInactive(err);
                startConnect();
            });
            return;
        }

        if (readSize) {
            _inc.sputn((const char *) _incBuf.data(), readSize);

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

    void Client::post(const message::Message::Ptr& msg, FutureListenerErrorCode listener) {
        asio::dispatch(_service, [this, msg, listener]() {
            MQTT_LOG(info) << "Send: " << _props.address << ":" << _props.port << ", " << mqttMsgName(msg->getType());

            auto identifier = dynamic_cast<MessagePacketIdentifier*>(msg.get());
            if (identifier) {
                identifier->setPacketIdentifier(++_packetIdentifier);
            }

            _encoder.encode(_out, msg);

            PromiseErrorCode promise;
            async_write(_socket, _out, [this, listener, promise = std::move(promise)](const ErrorCode& errorCode, std::size_t size) mutable {

                if (listener != nullptr) {
                    promise.set_value(errorCode);
                    listener(promise.get_future());
                }

                channelWriteComplete(errorCode, size);
            });
        });
    }

    void Client::channelWriteComplete(const ErrorCode &err, size_t writeSize) {
        if (err) {
            MQTT_LOG(info) << "Send Failed: " << _props.address << ":" << _props.port << ", " << err.message() << ", " << writeSize;
            asio::dispatch(_service, [this, err]() {
                channelInactive(err);
                startConnect();
            });
        }
    }
}