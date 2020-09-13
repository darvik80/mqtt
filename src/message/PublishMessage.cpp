//
// Created by Ivan Kishchenko on 12.09.2020.
//

#include "PublishMessage.h"

namespace mqtt::message {
    PublishMessage::PublishMessage(const std::string &topic, uint16_t packetIdentifier)
            : _topic(topic),_packetIdentifier(packetIdentifier) {

    }

    PublishMessage::PublishMessage() {

    }

    const std::string &PublishMessage::getTopic() const {
        return _topic;
    }

    void PublishMessage::setTopic(const std::string &topic) {
        _topic = topic;
    }

    [[maybe_unused]] uint16_t PublishMessage::getPacketIdentifier() const {
        return _packetIdentifier;
    }

    void PublishMessage::setPacketIdentifier(uint16_t packetIdentifier) {
        _packetIdentifier = packetIdentifier;
    }
}