//
// Created by Ivan Kishchenko on 12.09.2020.
//

#ifndef MQTT_PUBCOMPMESSAGE_H
#define MQTT_PUBCOMPMESSAGE_H

#include "Message.h"

namespace mqtt::message {

    class PubCompMessage : public Message {
    private:
        uint16_t _packetIdentifier{};
    public:
        [[nodiscard]] int getType() const override {
            return MQTT_MSG_PUBCOMP;
        }

        uint16_t getPacketIdentifier() const;

        void setPacketIdentifier(uint16_t packetIdentifier);
    };

}

#endif //MQTT_PUBCOMPMESSAGE_H