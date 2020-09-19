//
// Created by Ivan Kishchenko on 13.09.2020.
//

#ifndef MQTT_UNSUBACKMESSAGE_H
#define MQTT_UNSUBACKMESSAGE_H

#include "Message.h"

namespace mqtt::message {

    class UnSubAckMessage : public Message {
    private:
        uint16_t _packetIdentifier{};
    public:
        UnSubAckMessage() : Message(MQTT_MSG_UNSUBACK) { }

        [[nodiscard]] uint16_t getPacketIdentifier() const;

        void setPacketIdentifier(uint16_t packetIdentifier);
    };

}


#endif //MQTT_UNSUBACKMESSAGE_H
