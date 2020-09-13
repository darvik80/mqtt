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
        std::string _clientId;
        Flags _flags{};
    public:
        [[nodiscard]] int getType() const override {
            return MQTT_MSG_CONNECT;
        }

        [[nodiscard]] const Flags &getFlags() const;
        void setFlags(const Flags &flags);

        [[nodiscard]] const std::string &getClientId() const;
        void setClientId(const std::string &clientId);
    };
}


#endif //MQTT_CONNECTMESSAGE_H
