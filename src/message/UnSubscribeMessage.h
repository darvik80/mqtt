//
// Created by Ivan Kishchenko on 13.09.2020.
//

#ifndef MQTT_UNSUBSCRIBEMESSAGE_H
#define MQTT_UNSUBSCRIBEMESSAGE_H

#include <list>
#include "Message.h"

namespace mqtt::message {

    class UnSubscribeMessage : public Message {
    private:
        uint16_t _packetIdentifier;
        std::list<std::string> _topicFilters;
    public:
        [[nodiscard]] int getType() const override {
            return MQTT_MSG_UNSUBSCRIBE;
        }

        [[nodiscard]] uint16_t getPacketIdentifier() const;

        void setPacketIdentifier(uint16_t packetIdentifier);

        [[nodiscard]] const std::list<std::string> &getTopicFilters() const;

        void setTopicFilters(const std::list<std::string> &topicFilter);

        void addTopicFilter(const std::string& topicFilter);
    };

}


#endif //MQTT_UNSUBSCRIBEMESSAGE_H
