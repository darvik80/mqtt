//
// Created by Ivan Kishchenko on 13.09.2020.
//

#include "UnSubscribeMessage.h"

namespace mqtt::message {

    uint16_t UnSubscribeMessage::getPacketIdentifier() const {
        return _packetIdentifier;
    }

    void UnSubscribeMessage::setPacketIdentifier(uint16_t packetIdentifier) {
        _packetIdentifier = packetIdentifier;
    }

    const std::list<std::string> &UnSubscribeMessage::getTopicFilters() const {
        return _topicFilters;
    }

    void UnSubscribeMessage::setTopicFilters(const std::list<std::string> &topicFilter) {
        _topicFilters = topicFilter;
    }

    void UnSubscribeMessage::addTopicFilter(const std::string &topicFilter) {
        _topicFilters.push_back(topicFilter);
    }
}