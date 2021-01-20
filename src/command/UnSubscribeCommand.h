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
        std::string _topic{};
    public:
        UnSubscribeCommand(const Client::Ptr &client, std::string_view topic);

        boost::future<void> execute() override;
    };

}


#endif //MQTT_UNSUBSCRIBECOMMAND_H
