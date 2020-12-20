//
// Created by Ivan Kishchenko on 19.09.2020.
//

#include "Connection.h"

#include <utility>
#include "logging/Logger.h"

using namespace boost;
using namespace boost::asio;
using namespace mqtt::message;

namespace mqtt {

    Connection::Connection(const properties::ConnectionProperties &props)
            : Component("MQTTChannel")
            , _socket(IoServiceHolder::get_mutable_instance())
            , _endpoint(ip::address::from_string(props.address), props.port)
            , _incBuf(512)
            , _props(props) {
        startConnect();
    }

    void Connection::startConnect() {
        _socket.async_connect(_endpoint, [this](const boost::system::error_code &err) {
            if (!_socket.is_open() || err) {
                if (!_socket.is_open()) {
                    MQTT_LOG(warning) << name() << " Connect timed out";
                } else {
                    MQTT_LOG(error)  << name() << " Connect error: " << err.message();
                    _socket.close();
                }

                _timer = std::make_unique<Timer>("Reconnect Timer", [this]() { this->startConnect(); }, PosixSeconds{10});
                _timer->reset();
                _eventManager.raiseEvent(EventChannelActive{*this});
            } else {
                _timer.reset();
                MQTT_LOG(info) << name() << " Connected to " << _props.address << ":" << _props.port;
                _status = ACTIVE;

                startRead();

                this->channelActive();
            }

        });
    }

    void Connection::startRead() {
        _socket.async_read_some(
                boost::asio::buffer(_incBuf),
                [this](const boost::system::error_code &err, std::size_t size) {
                    this->channelReadComplete(err, size);
                }
        );
    }

    void Connection::onMessage(const message::Message::Ptr &msg) {
        MQTT_LOG(info) << name() << " Recv: " << mqttMsgName(msg->getType());
        _eventManager.raiseEvent(EventChannelMessage{*this, msg});
        switch (msg->getType()) {
            case MQTT_MSG_CONNACK: {
                auto ack = (ConnAckMessage *) msg.get();
                if (ack->getReasonCode()) {
                    MQTT_LOG(error) << "Session failed: " << ack->getReasonCodeDescription();
                    _socket.close();
                } else {
                    _status = CONNECTED;
                    MQTT_LOG(info) << "Session is active: " << _props.address << ":" << _props.port;;
                }
            }
                break;
            case MQTT_MSG_PINGRESP:
                break;
            case MQTT_MSG_DISCONNECT:
                _status = IDLE;
                break;
        }

        if (_status == CONNECTED) {
            _timer->reset();
        }
    }

    void Connection::channelActive() {
        _timer = std::make_unique<Timer>(
                "IdleTimer",
                [this]() {
                    post(std::make_shared<PingReqMessage>(), nullptr);
                },
                PosixSeconds{5}
        );
        _timer->reset();

        MQTT_LOG(info) << "Channel Active: " << _props.address << ":" << _props.port;
        auto msg = std::make_shared<ConnectMessage>("Rover");
        msg->setUserName(_props.username);
        msg->setPassword(_props.password);
        post(msg, nullptr);
    }

    void Connection::channelInactive(const ErrorCode &err) {
        if (err) {
            MQTT_LOG(error) << "Channel inactive: " << _props.address << ":" << _props.port << ", " << err.message();
        } else {
            MQTT_LOG(info) << "Channel inactive: " << _props.address << ":" << _props.port;
        }
        _eventManager.raiseEvent(EventChannelInactive{*this, err});
    }

    void Connection::channelReadComplete(const ErrorCode &err, size_t readSize) {
        if (err) {
            MQTT_LOG(warning) << "Read Failed: " << _props.address << ":" << _props.port << ", " << err.message();
            asio::dispatch(IoServiceHolder::get_mutable_instance(), [this, err]() {
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

    void Connection::post(const message::Message::Ptr &msg, FutureListenerErrorCode listener) {
        asio::dispatch(IoServiceHolder::get_mutable_instance(), [this, msg, listener]() {
            MQTT_LOG(info) << name() << " Send: " << _props.address << ":" << _props.port << ", " << mqttMsgName(msg->getType());

            auto identifier = dynamic_cast<MessagePacketIdentifier *>(msg.get());
            if (identifier) {
                identifier->setPacketIdentifier(++_packetIdentifier);
            }

            _encoder.encode(_out, msg);

            PromiseErrorCode promise;
            async_write(_socket, _out, [this, listener, promise = std::move(promise)](const ErrorCode &errorCode, std::size_t size) mutable {

                if (listener != nullptr) {
                    promise.set_value(errorCode);
                    listener(promise.get_future());
                }

                channelWriteComplete(errorCode, size);
            });
        });
    }

    void Connection::channelWriteComplete(const ErrorCode &err, size_t writeSize) {
        if (err) {
            MQTT_LOG(info) << "Send Failed: " << _props.address << ":" << _props.port << ", " << err.message() << ", " << writeSize;
            asio::dispatch(IoServiceHolder::get_mutable_instance(), [this, err]() {
                channelInactive(err);
                startConnect();
            });
        }
    }

    EventManager &Connection::getEventManager() {
        return _eventManager;
    }

    /*
    void Connection::post(const message::Message::Ptr& msg, PromiseErrorCode& promise) {
        asio::dispatch(IoServiceHolder::get_mutable_instance(), [this, msg, promise]() {
            MQTT_LOG(info) << name() << " Send: " << _props.address << ":" << _props.port << ", " << mqttMsgName(msg->getType());

            auto identifier = dynamic_cast<MessagePacketIdentifier *>(msg.get());
            if (identifier) {
                identifier->setPacketIdentifier(++_packetIdentifier);
            }

            _encoder.encode(_out, msg);

            PromiseErrorCode promise;
            async_write(_socket, _out, [this, listener, promise = std::move(promise)](const ErrorCode &errorCode, std::size_t size) mutable {

                if (listener != nullptr) {
                    promise.set_value(errorCode);
                    listener(promise.get_future());
                }

                channelWriteComplete(errorCode, size);
            });
        });
    }
     */
}