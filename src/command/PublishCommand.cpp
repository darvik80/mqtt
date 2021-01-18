//
// Created by Ivan Kishchenko on 26.12.2020.
//

#include <message/PubRelMessage.h>
#include <message/PubRecMessage.h>
#include <message/PubCompMessage.h>

#include <utility>
#include "PublishCommand.h"
#include "message/PublishMessage.h"
#include "message/PubAckMessage.h"

#include "message/QoS.h"

#include "logging/Logger.h"

namespace mqtt {

    class PublishResponseProcessor {
        uint8_t _id;
        uint16_t _waitMsgId;
        uint8_t _qos;
        Client::Ptr _client;
        const std::function<void(const ErrorCode &)> _callback;
    public:
        PublishResponseProcessor(uint8_t id, uint8_t qos, Client::Ptr client, std::function<void(const ErrorCode &)> callback)
                : _id(id), _qos(qos), _client(std::move(client)), _callback(std::move(callback)) {

            switch (_qos) {
                case message::QOS_AT_LEAST_ONCE:
                    _waitMsgId = message::MQTT_MSG_PUBACK;
                    break;
                case message::QOS_EXACTLY_ONCE:
                    _waitMsgId = message::MQTT_MSG_PUBREC;
                    break;
                default:
                    _waitMsgId = message::MQTT_MSG_RESERVED;
            }
        }

        bool process(const message::Message::Ptr& msg) {
            if (_qos == message::QOS_AT_LEAST_ONCE) {
                if (msg->getType() == _waitMsgId) {
                    auto *ack = dynamic_cast<message::PubAckMessage *>(msg.get());
                    if (ack && ack->getPacketIdentifier() == _id) {
                        _callback(ErrorCode{});
                        return false; // disconnect from event
                    }
                }

            } else if (_qos == message::QOS_EXACTLY_ONCE) {
                if (msg->getType() == _waitMsgId) {
                    if (msg->getType() == message::MQTT_MSG_PUBREC) {
                        auto *rec = dynamic_cast<message::PubRecMessage *>(msg.get());
                        if (rec && rec->getPacketIdentifier() == _id) {
                            auto rel = std::make_shared<message::PubRelMessage>();
                            rel->setPacketIdentifier(rec->getPacketIdentifier());
                            _client->post(rel).then([this](ErrorFuture future) {
                                auto err = future.get();
                                if (!err) {
                                    _waitMsgId = message::MQTT_MSG_PUBCOMP;
                                }

                                _callback(err);
                            });
                        }
                    } else if (msg->getType() == message::MQTT_MSG_PUBCOMP) {
                        auto *rel = dynamic_cast<message::PubRelMessage *>(msg.get());
                        if (rel && rel->getPacketIdentifier() == _id) {
                            _callback(ErrorCode{});
                            return false;
                        }
                    }
                }
            }

            return true; // continue receive events
        }
    };

    void PublishCommand::execute(const std::function<void(const ErrorCode &)> &callback) {
        auto msg = std::make_shared<message::PublishMessage>(_topic, _qos, _data);
        Client::Ptr client = _client;

        client->post(msg).then([msg, client, callback](ErrorFuture future) {
            auto err = future.get();
            if (!err) {
                auto processor = std::make_shared<PublishResponseProcessor>(msg->getPacketIdentifier(), msg->getQos(), client, callback);
                client->getEventManager()->subscribe<EventChannelMessage>([msg, processor, client, callback](const EventChannelMessage &event) -> bool {
                    if (!processor->process(msg)) {
                        MQTT_LOG(info) << "Publish confirmed";
                        return false; // disconnect from event
                    }

                    return true; // continue receive events
                });
            } else {
                callback(err);
            }
        });
    }

}