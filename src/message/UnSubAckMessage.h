//
// Created by Ivan Kishchenko on 13.09.2020.
//

#ifndef MQTT_UNSUBACKMESSAGE_H
#define MQTT_UNSUBACKMESSAGE_H

#include "Message.h"
#include "MessagePacketIdentifier.h"

namespace mqtt::message {

    class UnSubAckMessage : public Message, public MessagePacketIdentifier {
    public:
        UnSubAckMessage() : Message(MQTT_MSG_UNSUBACK) { }

    };

}


#endif //MQTT_UNSUBACKMESSAGE_H
