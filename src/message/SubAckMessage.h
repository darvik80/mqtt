//
// Created by Ivan Kishchenko on 13.09.2020.
//

#ifndef MQTT_SUBACKMESSAGE_H
#define MQTT_SUBACKMESSAGE_H

#include "Message.h"
#include "MessagePacketIdentifier.h"

namespace mqtt::message {

    class SubAckMessage : public Message, public MessagePacketIdentifier {
    private:
        uint8_t _returnCode{};
    public:
        SubAckMessage() : Message(MQTT_MSG_SUBACK){ }

        [[nodiscard]] uint8_t getReturnCode() const;

        void setReturnCode(uint8_t returnCode);
    };
}

#endif //MQTT_SUBACKMESSAGE_H
