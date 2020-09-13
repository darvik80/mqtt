//
// Created by Ivan Kishchenko on 12.09.2020.
//

#include "PubRelMessage.h"

namespace mqtt::message {

    uint16_t PubRelMessage::getPacketIdentifier() const {
        return _packetIdentifier;
    }

    void PubRelMessage::setPacketIdentifier(uint16_t packetIdentifier) {
        _packetIdentifier = packetIdentifier;
    }
}