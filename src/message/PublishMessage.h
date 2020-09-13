//
// Created by Ivan Kishchenko on 12.09.2020.
//

#ifndef MQTT_PUBLISHMESSAGE_H
#define MQTT_PUBLISHMESSAGE_H

#include "Message.h"

#include <string>

namespace mqtt::message {

    class PublishMessage : public Message {
    private:
        std::string _topic;

        uint16_t _packetIdentifier;
    public:
        PublishMessage(const std::string &topic, uint16_t packetIdentifier);
        PublishMessage();

        [[nodiscard]] int getType() const override {
            return MQTT_MSG_PUBLISH;
        }

        [[nodiscard]] const std::string &getTopic() const;

        void setTopic(const std::string &topic);

        [[maybe_unused]] uint16_t getPacketIdentifier() const;

        void setPacketIdentifier(uint16_t packetIdentifier);
    };

}


#endif //MQTT_PUBLISHMESSAGE_H
