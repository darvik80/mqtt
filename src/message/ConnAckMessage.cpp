//
// Created by Ivan Kishchenko on 12.09.2020.
//

#include "ConnAckMessage.h"

namespace mqtt::message {

    uint8_t ConnAckMessage::getReasonCode() const {
        return _rc;
    }

    void ConnAckMessage::setReasonCode(uint8_t rc) {
        _rc = rc;
    }

    uint8_t ConnAckMessage::getFlags() const {
        return _flags.all;
    }

    void ConnAckMessage::setFlags(uint8_t flags) {
        _flags.all = flags;
    }

}