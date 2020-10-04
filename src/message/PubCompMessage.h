//
// Created by Ivan Kishchenko on 12.09.2020.
//

#ifndef MQTT_PUBCOMPMESSAGE_H
#define MQTT_PUBCOMPMESSAGE_H

#include "Message.h"
#include "MessagePacketIdentifier.h"

namespace mqtt::message {

    class PubCompMessage : public Message, public MessagePacketIdentifier {
    public:
        PubCompMessage() : Message(MQTT_MSG_PUBCOMP){ }
    };

}

#endif //MQTT_PUBCOMPMESSAGE_H
