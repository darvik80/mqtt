//
// Created by Ivan Kishchenko on 12.09.2020.
//

#include "PubRecMessage.h"

namespace mqtt::message {

    uint16_t PubRecMessage::getPacketIdentifier() const {
        return _packetIdentifier;
    }

    void PubRecMessage::setPacketIdentifier(uint16_t packetIdentifier) {
        _packetIdentifier = packetIdentifier;
    }
}