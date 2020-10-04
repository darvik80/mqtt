//
// Created by Ivan Kishchenko on 12.09.2020.
//

#ifndef MQTT_PUBACKMESSAGE_H
#define MQTT_PUBACKMESSAGE_H

#include "Message.h"
#include "MessagePacketIdentifier.h"

namespace mqtt::message {

    class PubAckMessage : public Message,  public MessagePacketIdentifier {
    public:
        PubAckMessage() : Message(MQTT_MSG_PUBACK){ }
    };

}


#endif //MQTT_PUBACKMESSAGE_H
