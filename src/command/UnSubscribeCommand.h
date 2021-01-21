//
// Created by Ivan Kishchenko on 26.12.2020.
//

#ifndef MQTT_UNSUBSCRIBECOMMAND_H
#define MQTT_UNSUBSCRIBECOMMAND_H

#include "UserStd.h"
#include "Client.h"
#include "Command.h"

namespace mqtt {

    class UnSubscribeCommand : public Command, public std::enable_shared_from_this<UnSubscribeCommand> {
    private:
        std::string _topic{};
    private:
        UnSubscribeCommand(const Client::Ptr &client, std::string_view topic);
    public:
        template<typename ... T>
        static std::shared_ptr<UnSubscribeCommand> create(T &&... all) {
            return std::shared_ptr<UnSubscribeCommand>(new UnSubscribeCommand(std::forward<T>(all)...));
        }

        boost::future<void> execute() override;
    };

}


#endif //MQTT_UNSUBSCRIBECOMMAND_H
