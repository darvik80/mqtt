//
// Created by Ivan Kishchenko on 26.12.2020.
//

#ifndef MQTT_SUBSCRIBECOMMAND_H
#define MQTT_SUBSCRIBECOMMAND_H

#include "UserStd.h"
#include "Client.h"
#include "Command.h"

#include <message/SubscribeMessage.h>
#include <message/SubAckMessage.h>

#include <utility>

namespace mqtt {

    class SubscribeCommand : public Command,
                             public std::enable_shared_from_this<SubscribeCommand> {
    private:
        std::string _topic{};
        uint16_t _qos{};
    public:
        SubscribeCommand(const Client::Ptr &client, std::string_view topic, uint16_t qos)
                : Command(client), _topic(topic), _qos(qos) {}

        boost::future<void> execute() override;
    };
}

#endif //MQTT_SUBSCRIBECOMMAND_H
