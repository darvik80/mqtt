//
// Created by Ivan Kishchenko on 26.12.2020.
//

#ifndef MQTT_PUBLISHCOMMAND_H
#define MQTT_PUBLISHCOMMAND_H

#include "Command.h"
#include "Client.h"

namespace mqtt {
    class PublishCommand : public Command, public std::enable_shared_from_this<PublishCommand> {
    private:
        std::string _topic{};
        ByteBuffer _data;
        uint8_t _qos;
    public:
        PublishCommand(const Client::Ptr &client, std::string_view topic, uint8_t qos, const ByteBuffer &data)
                : Command(client), _topic(topic), _qos(qos), _data(data) {}

        PublishCommand(const Client::Ptr &client, std::string_view topic, uint8_t qos, std::string_view data)
                : Command(client), _topic(topic), _qos(qos), _data(data.begin(), data.end()) {
        }

        PublishCommand(const Client::Ptr &client, std::string_view topic, uint8_t qos, const char *data)
                : Command(client), _topic(topic), _qos(qos) {
            size_t size = strlen(data);
            _data.resize(size);
            std::copy((uint8_t*)data, (uint8_t*)(data + size), _data.begin());
        }

        boost::future<void> execute() override;
    };

}


#endif //MQTT_PUBLISHCOMMAND_H
