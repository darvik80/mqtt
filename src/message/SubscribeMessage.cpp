//
// Created by Ivan Kishchenko on 12.09.2020.
//

#include "SubscribeMessage.h"

namespace mqtt::message {

    const std::string &SubscribePayload::getTopicFilter() const {
        return _topicFilter;
    }

    void SubscribePayload::setTopicFilter(const std::string &topicFilter) {
        _topicFilter = topicFilter;
    }

    uint8_t SubscribePayload::getQos() const {
        return _requestedQos.all;
    }

    void SubscribePayload::setQos(uint8_t qos) {
        _requestedQos.all = qos;
    }

    SubscribePayload::SubscribePayload(const std::string &topicFilter, uint8_t qos)
    : _topicFilter(topicFilter)
    {
        _requestedQos.all = qos;
    }

    uint16_t SubscribeMessage::getPacketIdentifier() const {
        return _packetIdentifier;
    }

    void SubscribeMessage::setPacketIdentifier(uint16_t packetIdentifier) {
        _packetIdentifier = packetIdentifier;
    }

    const std::vector<SubscribePayload> &SubscribeMessage::getTopics() const {
        return _topics;
    }

    void SubscribeMessage::setTopics(const std::vector<SubscribePayload> &topics) {
        _topics = topics;
    }

    void SubscribeMessage::addTopic(const std::string &topicFilter, uint8_t qos) {
        _topics.emplace_back(topicFilter, qos)
    }
}