//
// Created by Ivan Kishchenko on 12.09.2020.
//

#ifndef MQTT_CONNECTMESSAGE_H
#define MQTT_CONNECTMESSAGE_H

#include <string>
#include "Message.h"

namespace mqtt::message {

    class ConnectMessage : public Message {
    private:
        std::string _protocolName{"MQIsdp"};
        uint8_t _protocolLevel{3};
        Flags _flags{0};
        std::string _clientId{};
        uint16_t _keepAlive{10};

        // connection data
        std::string _willTopic;
        std::string _willMessage;

        std::string _userName;
        std::string _password;
    public:
        ConnectMessage() : Message(MQTT_MSG_CONNECT){ }

        ConnectMessage(const std::string &clientId);

        [[nodiscard]] const std::string &getProtocolName() const;

        void setProtocolName(const std::string &protocolName);

        [[nodiscard]] uint8_t getProtocolLevel() const;

        void setProtocolLevel(uint8_t protocolLevel);

        [[nodiscard]] const std::string &getWillTopic() const;

        void setWillTopic(const std::string &willTopic);
        void setWillTopic(const std::string &willTopic, const std::string &willMessage);

        [[nodiscard]] const std::string &getWillMessage() const;

        void setWillMessage(const std::string &willMessage);

        [[nodiscard]] const std::string &getUserName() const;

        void setUserName(const std::string &userName);

        [[nodiscard]] const std::string &getPassword() const;

        void setPassword(const std::string &password);

        [[nodiscard]] const Flags &getFlags() const;
        void setFlags(uint8_t flags);

        [[nodiscard]] const std::string &getClientId() const;
        void setClientId(const std::string &clientId);

        [[nodiscard]] uint16_t getKeepAlive() const;

        void setKeepAlive(uint16_t keepAlive);
    };
}


#endif //MQTT_CONNECTMESSAGE_H
