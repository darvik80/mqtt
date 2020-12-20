//
// Created by Ivan Kishchenko on 12.09.2020.
//

#include "ConnectMessage.h"

namespace mqtt::message {

    const Flags &ConnectMessage::getFlags() const {
        return _flags;
    }


    void ConnectMessage::setFlags(uint8_t flags) {
        _flags.all = flags;
    }

    const std::string &ConnectMessage::getClientId() const {
        return _clientId;
    }

    void ConnectMessage::setClientId(const std::string &clientId) {
        _clientId = clientId;
    }

    uint16_t ConnectMessage::getKeepAlive() const {
        return _keepAlive;
    }

    void ConnectMessage::setKeepAlive(uint16_t keepAlive) {
        _keepAlive = keepAlive;
    }

    const std::string &ConnectMessage::getProtocolName() const {
        return _protocolName;
    }

    void ConnectMessage::setProtocolName(const std::string &protocolName) {
        _protocolName = protocolName;
    }

    uint8_t ConnectMessage::getProtocolLevel() const {
        return _protocolLevel;
    }

    void ConnectMessage::setProtocolLevel(uint8_t protocolLevel) {
        _protocolLevel = protocolLevel;
    }

    const std::string &ConnectMessage::getWillTopic() const {
        return _willTopic;
    }

    void ConnectMessage::setWillTopic(const std::string &willTopic) {
        setWillTopic(willTopic, "");
    }

    void ConnectMessage::setWillTopic(const std::string &willTopic, const std::string &willMessage) {
        _flags.bits.willFlag = true;
        _willTopic = willTopic;
        _willMessage = willMessage;
    }

    const std::string &ConnectMessage::getWillMessage() const {
        return _willMessage;
    }

    void ConnectMessage::setWillMessage(const std::string &willMessage) {
        _willMessage = willMessage;
    }

    const std::string &ConnectMessage::getUserName() const {
        return _userName;
    }

    void ConnectMessage::setUserName(const std::string &userName) {
        _flags.bits.username = !userName.empty();
        _userName = userName;
    }

    const std::string &ConnectMessage::getPassword() const {
        return _password;
    }

    void ConnectMessage::setPassword(const std::string &password) {
        _flags.bits.password = !password.empty();
        _password = password;
    }

    ConnectMessage::ConnectMessage(const std::string &clientId) : Message(MQTT_MSG_CONNECT), _clientId(clientId) {}
}