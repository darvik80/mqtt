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
        typedef std::shared_ptr<Message> Ptr;
        typedef std::unique_ptr<Message> AutoPtr;

    private:
        Header _header{};

        uint32_t _size{};
    public:
        explicit Message(uint8_t type);

        void setQos(uint8_t qos) {
            _header.bits.qos = qos;
        }

        void setRetain(bool retain) {
            _header.bits.retain = retain;
        }

        [[nodiscard]] virtual uint8_t getType() const  {
            return _header.bits.type;
        }

        [[nodiscard]] const Header &getHeader() const;

        void setHeader(uint8_t header);

        [[nodiscard]] uint32_t getSize() const;

        void setSize(uint32_t size);

        virtual ~Message() = default;
    };

}


#endif //MQTT_MESSAGE_H
