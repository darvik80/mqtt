//
// Created by Ivan Kishchenko on 12.09.2020.
//

#ifndef MQTT_PUBLISHMESSAGE_H
#define MQTT_PUBLISHMESSAGE_H

#include "Message.h"

#include <string>
#include <vector>

namespace mqtt::message {

    class PublishMessage : public Message {
    private:
        std::string _topic;
        std::vector<uint8_t> _message;

        uint16_t _packetIdentifier{};
    public:
        PublishMessage(const std::string &topic, uint16_t packetIdentifier);

        PublishMessage() : Message(MQTT_MSG_PUBLISH) {
            setRetain(true);
        }

        [[nodiscard]] const std::string &getTopic() const;

        void setTopic(const std::string &topic);

        [[nodiscard]] const std::vector<uint8_t> &getMessage() const;

        void setMessage(const std::vector<uint8_t> &message);
        void setMessage(const uint8_t* message, size_t size);
        void setMessage(const std::string& message);

        [[nodiscard]] uint16_t getPacketIdentifier() const;

        void setPacketIdentifier(uint16_t packetIdentifier);
    };

}


#endif //MQTT_PUBLISHMESSAGE_H
