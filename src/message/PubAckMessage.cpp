//
// Created by Ivan Kishchenko on 12.09.2020.
//

#include "PubAckMessage.h"

namespace mqtt::message {

    uint16_t PubAckMessage::getPacketIdentifier() const {
        return _packetIdentifier;
    }

    void PubAckMessage::setPacketIdentifier(uint16_t packetIdentifier) {
        _packetIdentifier = packetIdentifier;
    }
}