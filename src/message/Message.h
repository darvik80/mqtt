//
// Created by Ivan Kishchenko on 12.09.2020.
//

#ifndef MQTT_MESSAGE_H
#define MQTT_MESSAGE_H

#include <memory>
#include "Packet.h"

namespace mqtt::message {

    class Message {
    public:
        typedef std::shared_ptr<Message> MessagePtr;

    private:
        Header _header{};
    public:
        [[nodiscard]] virtual int getType() const = 0;

        [[nodiscard]] const Header &getHeader() const;
    };

}


#endif //MQTT_MESSAGE_H
