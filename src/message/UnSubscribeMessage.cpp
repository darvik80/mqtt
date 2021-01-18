//
// Created by Ivan Kishchenko on 13.09.2020.
//

#include "UnSubscribeMessage.h"

namespace mqtt::message {

    const std::vector<std::string> &UnSubscribeMessage::getTopicFilters() const {
        return _topicFilters;
    }

    void UnSubscribeMessage::addTopicFilter(const std::string &topicFilter) {
        _topicFilters.push_back(topicFilter);
    }
}