//
// Created by Ivan Kishchenko on 12.09.2020.
//

#include "ConnectMessage.h"

namespace mqtt::message {

    const Flags &ConnectMessage::getFlags() const {
        return _flags;
    }

    void ConnectMessage::setFlags(const mqtt::Flags &flags) {
        _flags = flags;
    }

    const std::string &ConnectMessage::getClientId() const {
        return _clientId;
    }

    void ConnectMessage::setClientId(const std::string &clientId) {
        _clientId = clientId;
    }
}