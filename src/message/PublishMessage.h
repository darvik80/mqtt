//
// Created by Ivan Kishchenko on 12.09.2020.
//

#ifndef MQTT_PUBLISHMESSAGE_H
#define MQTT_PUBLISHMESSAGE_H

#include "Message.h"
#include "MessagePacketIdentifier.h"

#include <string>
#include <vector>

namespace mqtt::message {

    class PublishMessage : public Message, public MessagePacketIdentifier {
    private:
        std::string _topic;
        std::vector<uint8_t> _message;
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
    };

}


#endif //MQTT_PUBLISHMESSAGE_H
