//
// Created by Ivan Kishchenko on 12.09.2020.
//

#include "PublishMessage.h"

namespace mqtt::message {
    PublishMessage::PublishMessage(const std::string &topic, uint16_t packetIdentifier)
            : Message(MQTT_MSG_PUBLISH), _topic(topic), _packetIdentifier(packetIdentifier) {
        setRetain(true);
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

    const std::vector<uint8_t> &PublishMessage::getMessage() const {
        return _message;
    }

    void PublishMessage::setMessage(const std::vector<uint8_t> &message) {
        _message = message;
    }

    void PublishMessage::setMessage(const uint8_t *message, size_t size) {
        _message.resize(size);
        memcpy(_message.data(), message, size);
    }

    void PublishMessage::setMessage(const std::string &message) {
        _message.resize(message.size());
        memcpy(_message.data(), message.c_str(), message.size());
    }
}