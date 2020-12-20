//
// Created by Ivan Kishchenko on 12.09.2020.
//

#include "ConnAckMessage.h"

namespace mqtt::message {

    uint8_t ConnAckMessage::getReasonCode() const {
        return _rc;
    }

    const char* ConnAckMessage::getReasonCodeDescription() const {
        switch (_rc) {
            case RESP_CODE_ACCEPTED:
                return "Connection accepted";
            case RESP_CODE_UNACCEPTABLE_PROTOCOL_VERSION:
                return "Connection refused, unacceptable protocol version";
            case RESP_CODE_IDENTIFIER_REJECTED:
                return "Connection refused, identifier rejected";
            case RESP_CODE_SERVER_UNAVAILABLE:
                return "Connection refused, server unavailable";
            case RESP_CODE_BAD_USER_NAME_OR_PASSWORD:
                return "Connection refused, bad user name or password";
            case RESP_CODE_NOT_AUTHORIZED:
                return "Connection refused, not authorized";
        }

        return "Unknown response";
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