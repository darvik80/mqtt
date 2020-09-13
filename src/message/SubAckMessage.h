//
// Created by Ivan Kishchenko on 13.09.2020.
//

#ifndef MQTT_SUBACKMESSAGE_H
#define MQTT_SUBACKMESSAGE_H

#include "Message.h"

namespace mqtt::message {

    class SubAckMessage : public Message {
    private:
        uint16_t _packetIdentifier{};
        uint8_t _returnCode{};
    public:
        [[nodiscard]] int getType() const override {
            return MQTT_MSG_SUBACK;
        }

        uint16_t getPacketIdentifier() const;

        void setPacketIdentifier(uint16_t packetIdentifier);

        uint8_t getReturnCode() const;

        void setReturnCode(uint8_t returnCode);
    };

}

#endif //MQTT_SUBACKMESSAGE_H