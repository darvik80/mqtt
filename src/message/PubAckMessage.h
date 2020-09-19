//
// Created by Ivan Kishchenko on 12.09.2020.
//

#ifndef MQTT_PUBACKMESSAGE_H
#define MQTT_PUBACKMESSAGE_H

#include "Message.h"

namespace mqtt::message {

    class PubAckMessage : public Message {
    private:
        uint16_t _packetIdentifier{};
    public:
        PubAckMessage() : Message(MQTT_MSG_PUBACK){ }

        [[nodiscard]] uint16_t getPacketIdentifier() const;

        void setPacketIdentifier(uint16_t packetIdentifier);
    };

}


#endif //MQTT_PUBACKMESSAGE_H
