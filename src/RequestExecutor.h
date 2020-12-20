//
// Created by Ivan Kishchenko on 20.12.2020.
//

#ifndef MQTT_REQUESTEXECUTOR_H
#define MQTT_REQUESTEXECUTOR_H

#include "Future.h"
#include "Connection.h"

namespace mqtt {
    class RequestExecutor {
    private:
        Connection& _connection;
    public:
        RequestExecutor(Connection& _connection);

        FutureErrorCode subscribe(std::string_view topic);
    };

}


#endif //MQTT_REQUESTEXECUTOR_H
