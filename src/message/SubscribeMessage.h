//
// Created by Ivan Kishchenko on 12.09.2020.
//

#ifndef MQTT_SUBSCRIBEMESSAGE_H
#define MQTT_SUBSCRIBEMESSAGE_H

#include <string>
#include <vector>
#include "Message.h"

namespace mqtt::message {

    class SubscribePayload {
    private:
        std::string _topicFilter;
        union {
            uint8_t all;    /**< all connack flags */
            struct {
                unsigned int reserved : 7;    /**< message type nibble */
                unsigned int qos : 3;    /**< message type nibble */
            } bits;
        } _requestedQos{};     /**< connack flags byte */
    public:
        SubscribePayload(const std::string &topicFilter, uint8_t qos);

        [[nodiscard]] const std::string &getTopicFilter() const;

        [[nodiscard]] uint8_t getQos() const;
    };

    class SubscribeMessage : public Message {
    private:
        uint16_t _packetIdentifier{};

        std::vector<SubscribePayload> _topics;
    public:
        SubscribeMessage() : Message(MQTT_MSG_SUBSCRIBE) { }

        [[nodiscard]] uint16_t getPacketIdentifier() const;

        void setPacketIdentifier(uint16_t packetIdentifier);

        [[nodiscard]] const std::vector<SubscribePayload> &getTopics() const;


        void addTopic(const std::string &topicFilter, uint8_t qos);
    };

}


#endif //MQTT_SUBSCRIBEMESSAGE_H
