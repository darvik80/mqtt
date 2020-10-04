//
// Created by Kishchenko, Ivan on 9/30/20.
//

#ifndef MQTT_FUTURE_H
#define MQTT_FUTURE_H

#include <exception/Exception.h>
#include <boost/system/error_code.hpp>
#include <message/Message.h>
#include "UserStd.h"

namespace mqtt {

    typedef std::promise<ErrorCode> PromiseErrorCode;
    typedef std::future<ErrorCode> FutureErrorCode;
    typedef std::function<void(const FutureErrorCode &)> FutureListenerErrorCode;
}

#endif //MQTT_FUTURE_H
