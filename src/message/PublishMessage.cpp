//
// Created by Ivan Kishchenko on 12.09.2020.
//

#include "PublishMessage.h"
#include <cstring>

namespace mqtt::message {
    PublishMessage::PublishMessage(std::string_view topic, uint16_t packetIdentifier)
            : Message(MQTT_MSG_PUBLISH), _topic(topic) {
        setRetain(false);
        setPacketIdentifier(packetIdentifier);
    }

    PublishMessage::PublishMessage(std::string_view topic, uint8_t qos, uint16_t packetIdentifier, std::string_view data)
            : Message(MQTT_MSG_PUBLISH), _topic(topic) {
        setRetain(false);
        setQos(qos);
        setPacketIdentifier(packetIdentifier);
        setMessage((const uint8_t*)data.data(), data.size());
    }


    PublishMessage::PublishMessage(std::string_view topic, uint8_t qos, uint16_t packetIdentifier, const std::vector<uint8_t>& data)
            : Message(MQTT_MSG_PUBLISH), _topic(topic) {
        setRetain(false);
        setQos(qos);
        setMessage(data);
    }


    const std::string &PublishMessage::getTopic() const {
        return _topic;
    }

    void PublishMessage::setTopic(const std::string &topic) {
        _topic = topic;
    }

    const std::vector<uint8_t> &PublishMessage::getMessage() const {
        return _message;
    }

    void PublishMessage::setMessage(const std::vector<uint8_t> &message) {
        _message = message;
    }

    void PublishMessage::setMessage(const uint8_t *message, size_t size) {
        _message.resize(size);
        std::memcpy(_message.data(), message, size);
    }

    void PublishMessage::setMessage(const std::string &message) {
        _message.resize(message.size());
        std::memcpy(_message.data(), message.c_str(), message.size());
    }

}