//
// Created by Ivan Kishchenko on 12.09.2020.
//

#ifndef MQTT_PUBRELMESSAGE_H
#define MQTT_PUBRELMESSAGE_H

#include "Message.h"

namespace mqtt::message {

    class PubRelMessage : public Message {
    private:
        uint16_t _packetIdentifier{};
    public:
        PubRelMessage() : Message(MQTT_MSG_PUBREL){ }

        [[nodiscard]] uint16_t getPacketIdentifier() const;

        void setPacketIdentifier(uint16_t packetIdentifier);
    };

}

#endif //MQTT_PUBRELMESSAGE_H
