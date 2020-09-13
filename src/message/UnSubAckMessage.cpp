//
// Created by Ivan Kishchenko on 13.09.2020.
//

#include "UnSubAckMessage.h"

namespace mqtt::message {

    uint16_t UnSubAckMessage::getPacketIdentifier() const {
        return _packetIdentifier;
    }

    void UnSubAckMessage::setPacketIdentifier(uint16_t packetIdentifier) {
        _packetIdentifier = packetIdentifier;
    }
};