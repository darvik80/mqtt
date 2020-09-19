//
// Created by Ivan Kishchenko on 12.09.2020.
//

#ifndef MQTT_PUBRECMESSAGE_H
#define MQTT_PUBRECMESSAGE_H

#include "Message.h"

namespace mqtt::message {

    class PubRecMessage : public Message  {
    private:
        uint16_t _packetIdentifier{};
    public:
        PubRecMessage() : Message(MQTT_MSG_PUBREC){ }

        [[nodiscard]] uint16_t getPacketIdentifier() const;

        void setPacketIdentifier(uint16_t packetIdentifier);
    };

}

#endif //MQTT_PUBRECMESSAGE_H
