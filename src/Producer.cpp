//
// Created by Ivan Kishchenko on 04.10.2020.
//

#include "Producer.h"

namespace mqtt {

    DefaultProducer::DefaultProducer(Client &client) : _client(client) {}

    void DefaultProducer::publish(const std::string &topic, const std::string &msg) {
        auto pubMsg = std::make_shared<message::PublishMessage>();
        pubMsg->setTopic(topic);
        pubMsg->setMessage(msg);

        _client.write(pubMsg, nullptr);
    }


}
