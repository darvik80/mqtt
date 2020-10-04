//
// Created by Ivan Kishchenko on 12.09.2020.
//

#ifndef MQTT_PUBRELMESSAGE_H
#define MQTT_PUBRELMESSAGE_H

#include "Message.h"
#include "MessagePacketIdentifier.h"

namespace mqtt::message {

    class PubRelMessage : public Message, public MessagePacketIdentifier {
    public:
        PubRelMessage() : Message(MQTT_MSG_PUBREL){ }
    };

}

#endif //MQTT_PUBRELMESSAGE_H
