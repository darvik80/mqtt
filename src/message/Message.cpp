//
// Created by Ivan Kishchenko on 12.09.2020.
//

#include "Message.h"

namespace mqtt::message {
    Message::Message(uint8_t type)  {
        _header.bits.type = type;
    }

    const char *Message::getTypeStr() const {
        return mqttMsgName(getType());
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