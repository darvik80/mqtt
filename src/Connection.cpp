//
// Created by Ivan Kishchenko on 19.09.2020.
//

#include "Connection.h"

#include <utility>
#include "logging/Logger.h"
#include <boost/lexical_cast.hpp>
#include "exception/SystemException.h"

using namespace boost;
using namespace boost::asio;
using namespace mqtt::message;

namespace mqtt {

    DefaultConnection::DefaultConnection(const properties::ConnectionProperties &props)
            : Component("MQTTChannel")
            , _socket(IoServiceHolder::get_mutable_instance())
            , _incBuf(512)
            , _props(props) {
        // TODO: make it async
        ip::tcp::resolver::query resolver_query(props.address, lexical_cast<std::string>(props.port));
        boost::asio::ip::tcp::resolver _resolver(IoServiceHolder::get_mutable_instance());
        auto iterator = _resolver.resolve(resolver_query);
        _endpoint = *iterator;
    }

    void DefaultConnection::start() {
        _shutdown = false;
        startConnect();
    }

    void DefaultConnection::stop() {
        asio::dispatch(IoServiceHolder::get_mutable_instance(), [this]() {
            _shutdown = true;
            _socket.close();
        });
    }

    void DefaultConnection::startConnect() {
        if (_shutdown) {
            return;
        }
        _socket.async_connect(_endpoint, [this](const boost::system::error_code &err) {
            if (!_socket.is_open() || err) {
                if (!_socket.is_open()) {
                    MQTT_LOG(warning) << name() << " Connect timed out";
                } else {
                    MQTT_LOG(error) << name() << " Connect error: " << err.message();
                    _socket.close();
                }

                _timer = std::make_unique<Timer>("Reconnect Timer", [this]() { this->startConnect(); }, PosixSeconds{10});
                _timer->reset();
            } else {
                MQTT_LOG(info) << name() << " Connected to " << _props.address << ":" << _props.port;
                _status = ACTIVE;

                startRead();
                this->channelActive();
            }

        });
    }

    void DefaultConnection::startRead() {
        _socket.async_read_some(
                boost::asio::buffer(_incBuf),
                [this](const boost::system::error_code &err, std::size_t size) {
                    this->channelReadComplete(err, size);
                }
        );
    }

    void DefaultConnection::onMessage(const message::Message::Ptr &msg) {
        _lastUpdate = boost::posix_time::second_clock::local_time();
        MQTT_LOG(info) << name() << " Recv: " << msg->getTypeStr();
        raiseEvent(EventChannelMessage{*this, msg});
        switch (msg->getType()) {
            case MQTT_MSG_CONNACK: {
                auto ack = (ConnAckMessage *) msg.get();
                if (ack->getReasonCode()) {
                    MQTT_LOG(error) << "Session failed: " << ack->getReasonCodeDescription();
                    _socket.close();
                } else {
                    _status = CONNECTED;
                    MQTT_LOG(info) << "Session is active: " << _props.address << ":" << _props.port;;
                    raiseEvent(EventChannelActive{*this});
                    _timer = std::make_unique<Timer>(
                            "IdleTimer",
                            [this]() {
                                PosixTime now = boost::posix_time::second_clock::local_time();
                                if ((now - _lastUpdate) > PosixSeconds{10}) {
                                    _socket.close();
                                } else {
                                    post(std::make_shared<PingReqMessage>());
                                }
                            },
                            PosixSeconds{5}
                    );
                    _timer->reset();
                }
            }
                break;
            case MQTT_MSG_PUBLISH: {
                auto pub = (PublishMessage *) msg.get();
                if (pub->getQos() >= message::QOS_AT_LEAST_ONCE) {
                    post(std::make_shared<message::PubAckMessage>(pub->getPacketIdentifier()));
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

    void DefaultConnection::channelActive() {
        _timer = std::make_unique<Timer>("ConnTimer", [this]() { this->_socket.close(); }, PosixSeconds{5});
        _timer->reset();

        MQTT_LOG(info) << "Channel Active: " << _props.address << ":" << _props.port;
        auto msg = std::make_shared<ConnectMessage>("Rover");
        msg->setUserName(_props.username);
        msg->setPassword(_props.password);
        post(msg);
    }

    void DefaultConnection::channelInactive(const ErrorCode &err) {
        if (err) {
            MQTT_LOG(error) << "Channel inactive: " << _props.address << ":" << _props.port << ", " << err.message();

            _socket.close();
            asio::dispatch(IoServiceHolder::get_mutable_instance(), [this]() {
                startConnect();
            });
        } else {
            MQTT_LOG(info) << "Channel inactive: " << _props.address << ":" << _props.port;
        }
        raiseEvent(EventChannelInactive{*this, err});
    }

    void DefaultConnection::channelReadComplete(const ErrorCode &err, size_t readSize) {
        if (err) {
            MQTT_LOG(warning) << "Read Failed: " << _props.address << ":" << _props.port << ", " << err.message();
            channelInactive(err);
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

    ErrorFuture DefaultConnection::post(const message::Message::Ptr &msg) {
        auto promise = std::make_shared<ErrorPromise>();

        asio::dispatch(IoServiceHolder::get_mutable_instance(), [this, msg, promise]() {
            if (msg->getType() != MQTT_MSG_CONNECT && _status != CONNECTED) {
                MQTT_LOG(info) << name() << " " << msg->getTypeStr() << " ignored";
                promise->set_value(ErrorCode{});
                return;
            }

            MQTT_LOG(info) << name() << " Send: " << _props.address << ":" << _props.port << ", " << msg->getTypeStr();

            // TODO remove it
            auto identifier = dynamic_cast<MessagePacketIdentifier *>(msg.get());
            if (identifier && identifier->getPacketIdentifier() == 0) {
                identifier->setPacketIdentifier(++_packetIdentifier);
            }
            _encoder.encode(_out, msg);

            async_write(_socket, _out, [this, promise](const ErrorCode &errorCode, std::size_t size) mutable {
                promise->set_value(errorCode);
                channelWriteComplete(errorCode, size);
            });
        });

        return promise->get_future();
    }

    void DefaultConnection::channelWriteComplete(const ErrorCode &err, size_t writeSize) {
        if (err) {
            MQTT_LOG(info) << "Send Failed: " << _props.address << ":" << _props.port << ", " << err.message() << ", " << writeSize;
            channelInactive(err);
        }
    }

    void DefaultConnection::setEventManager(EventManager::Ptr eventManager) {
        this->_eventManager = eventManager;
    }
}