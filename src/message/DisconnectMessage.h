//
// Created by Ivan Kishchenko on 13.09.2020.
//

#ifndef MQTT_DISCONNECTMESSAGE_H
#define MQTT_DISCONNECTMESSAGE_H

#include "Message.h"

namespace mqtt::message {

    class DisconnectMessage : public Message {
        [[nodiscard]] int getType() const override {
            return MQTT_MSG_DISCONNECT;
        }

    };

}


#endif //MQTT_DISCONNECTMESSAGE_H
