//
// Created by Ivan Kishchenko on 26.12.2020.
//

#ifndef MQTT_UNSUBSCRIBECOMMAND_H
#define MQTT_UNSUBSCRIBECOMMAND_H

#include "UserStd.h"
#include "Client.h"
#include "Command.h"

namespace mqtt {

    class UnSubscribeCommand : public Command {
    private:
        Client::Ptr _client{};

        std::string _topic{};
    public:
        UnSubscribeCommand(const Client::Ptr &client, std::string_view topic);

        void execute(const std::function<void(const ErrorCode&)> &callback) override;
    };

}


#endif //MQTT_UNSUBSCRIBECOMMAND_H
