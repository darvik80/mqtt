//
// Created by Ivan Kishchenko on 13.09.2020.
//

#ifndef MQTT_UNSUBSCRIBEMESSAGE_H
#define MQTT_UNSUBSCRIBEMESSAGE_H

#include <vector>
#include <string>
#include "Message.h"

namespace mqtt::message {

    class UnSubscribeMessage : public Message {
    private:
        uint16_t _packetIdentifier;
        std::vector<std::string> _topicFilters;
    public:
        UnSubscribeMessage() : Message(MQTT_MSG_UNSUBSCRIBE) { }

        [[nodiscard]] uint16_t getPacketIdentifier() const;

        void setPacketIdentifier(uint16_t packetIdentifier);

        [[nodiscard]] const std::vector<std::string> &getTopicFilters() const;

        void addTopicFilter(const std::string& topicFilter);
    };

}


#endif //MQTT_UNSUBSCRIBEMESSAGE_H
