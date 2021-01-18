//
// Created by Ivan Kishchenko on 26.12.2020.
//

#ifndef MQTT_SUBSCRIBECOMMAND_H
#define MQTT_SUBSCRIBECOMMAND_H

#include "UserStd.h"
#include "Client.h"
#include "Command.h"

namespace mqtt {

    class SubscribeCommand : public Command {
    private:
        Client::Ptr _client{};

        std::string _topic{};
        uint16_t _qos{};
    public:
        SubscribeCommand(const Client::Ptr &client, std::string_view topic, uint16_t qos)
                : _client(client), _topic(topic), _qos(qos) {}

        void execute(const std::function<void(const ErrorCode&)> &callback) override;
    };
}

#endif //MQTT_SUBSCRIBECOMMAND_H
