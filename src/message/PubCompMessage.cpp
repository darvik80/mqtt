//
// Created by Ivan Kishchenko on 12.09.2020.
//

#include "PubCompMessage.h"

namespace mqtt::message {

    uint16_t PubCompMessage::getPacketIdentifier() const {
        return _packetIdentifier;
    }

    void PubCompMessage::setPacketIdentifier(uint16_t packetIdentifier) {
        _packetIdentifier = packetIdentifier;
    }
}