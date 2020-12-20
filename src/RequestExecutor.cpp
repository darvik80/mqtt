//
// Created by Ivan Kishchenko on 20.12.2020.
//

#include "RequestExecutor.h"

#include "message/SubscribeMessage.h"
#include "message/SubAckMessage.h"

namespace mqtt {

    RequestExecutor::RequestExecutor(Connection& connection)
    : _connection(connection)
    {}

    FutureErrorCode RequestExecutor::subscribe(std::string_view topic) {
        PromiseErrorCode promise;

        auto msg = std::make_shared<message::SubscribeMessage>();
        msg->addTopic(topic, QOS_AT_MOST_ONCE)
        _connection.post(msg, [this, promise](const FutureErrorCode& err) {

        });
        return mqtt::FutureErrorCode();
    }
}