//
// Created by Ivan Kishchenko on 12.09.2020.
//

#ifndef MQTT_PUBRECMESSAGE_H
#define MQTT_PUBRECMESSAGE_H

#include "Message.h"
#include "MessagePacketIdentifier.h"

namespace mqtt::message {

    class PubRecMessage : public Message, public MessagePacketIdentifier  {
    public:
        PubRecMessage() : Message(MQTT_MSG_PUBREC){ }
    };

}

#endif //MQTT_PUBRECMESSAGE_H
