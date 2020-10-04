//
// Created by Ivan Kishchenko on 13.09.2020.
//

#ifndef MQTT_UNSUBSCRIBEMESSAGE_H
#define MQTT_UNSUBSCRIBEMESSAGE_H

#include <vector>
#include <string>
#include "Message.h"
#include "MessagePacketIdentifier.h"

namespace mqtt::message {

    class UnSubscribeMessage : public Message, public MessagePacketIdentifier {
    private:
        std::vector<std::string> _topicFilters;
    public:
        UnSubscribeMessage() : Message(MQTT_MSG_UNSUBSCRIBE) { }

        [[nodiscard]] const std::vector<std::string> &getTopicFilters() const;

        void addTopicFilter(const std::string& topicFilter);
    };

}


#endif //MQTT_UNSUBSCRIBEMESSAGE_H
