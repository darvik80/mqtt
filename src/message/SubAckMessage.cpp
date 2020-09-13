//
// Created by Ivan Kishchenko on 13.09.2020.
//

#include "SubAckMessage.h"

namespace mqtt::message {

    uint16_t SubAckMessage::getPacketIdentifier() const {
        return _packetIdentifier;
    }

    void SubAckMessage::setPacketIdentifier(uint16_t packetIdentifier) {
        _packetIdentifier = packetIdentifier;
    }

    uint8_t SubAckMessage::getReturnCode() const {
        return _returnCode;
    }

    void SubAckMessage::setReturnCode(uint8_t returnCode) {
        _returnCode = returnCode;
    }
}