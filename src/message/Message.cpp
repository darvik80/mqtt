//
// Created by Ivan Kishchenko on 12.09.2020.
//

#include "Message.h"

namespace mqtt::message {
    Message::Message(uint8_t type)  {
        _header.bits.type = type;
    }

    struct {
        MessageType value;
        const char *name;
    } mqttNameToString[] = {
            {MQTT_MSG_RESERVED, "UNKNOWN"},
            {MQTT_MSG_CONNECT, "CONNECT"},
            {MQTT_MSG_CONNACK, "CONNACK"},
            {MQTT_MSG_PUBLISH, "PUBLICH"},
            {MQTT_MSG_PUBACK, "PUBACK"},
            {MQTT_MSG_PUBREC, "PUBREC"},
            {MQTT_MSG_PUBREL, "PUBREL"},
            {MQTT_MSG_PUBCOMP, "PUBCOMP"},
            {MQTT_MSG_SUBSCRIBE, "SUBSCRIBE"},
            {MQTT_MSG_SUBACK, "SUBACK"},
            {MQTT_MSG_UNSUBSCRIBE, "UNSUBSCRIBE"},
            {MQTT_MSG_UNSUBACK, "UNSUBACK"},
            {MQTT_MSG_PINGREQ, "PINGREQ"},
            {MQTT_MSG_PINGRESP, "PINGRESP"},
            {MQTT_MSG_DISCONNECT, "DISCONNECT"}

    };

    const char *Message::getTypeStr() const {
        return mqttNameToString[getType()].name;
    }

    const Header &Message::getHeader() const {
        return _header;
    }

    void Message::setHeader(uint8_t header) {
        _header.all = header;
    }

    uint32_t Message::getSize() const {
        return _size;
    }

    void Message::setSize(uint32_t size) {
        _size = size;
    }

}