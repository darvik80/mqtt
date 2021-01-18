//
// Created by Ivan Kishchenko on 26.12.2020.
//

#ifndef MQTT_PUBLISHER_H
#define MQTT_PUBLISHER_H

#include "command/PublishCommand.h"
#include "Client.h"

namespace mqtt {

    class Publisher {
        Client::Ptr _client;
        std::string _topic;
        uint8_t _qos;
    public:
        Publisher(const Client::Ptr &client, std::string_view topic, uint8_t qos)
                : _client(client), _topic(topic), _qos(qos) {}

        void publish(const ByteBuffer& data) {
            PublishCommand cmd{_client, _topic, _qos, data};
            cmd.execute([this](const ErrorCode &err) {
                if (err) {
                    MQTT_LOG(info) << "Can't publish to: " << _topic << ", error: " << err.message();
                }
            });
        }

        void publish(std::string_view data) {
            PublishCommand cmd{_client, _topic, _qos, data};
            cmd.execute([this](const ErrorCode &err) {
                if (err) {
                    MQTT_LOG(info) << "Can't publish to: " << _topic << ", error: " << err.message();
                }
            });
        }

        void publish(const char* data) const {
            PublishCommand cmd{_client, _topic, _qos, data};
            cmd.execute([this](const ErrorCode &err) {
                if (err) {
                    MQTT_LOG(info) << "Can't publish to: " << _topic << ", error: " << err.message();
                }
            });
        }
    };

}


#endif //MQTT_PUBLISHER_H
