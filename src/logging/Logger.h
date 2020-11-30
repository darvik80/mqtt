//
// Created by Kishchenko, Ivan on 10/2/20.
//

#ifndef MQTT_LOGGER_H
#define MQTT_LOGGER_H

#include <boost/log/trivial.hpp>
#include "properties/LoggerProperties.h"

#define MQTT_LOG(level)  BOOST_LOG_TRIVIAL(level)

namespace mqtt::logging {

    class Logger {
    public:
        static void init(const properties::LoggerProperties& props);
    };

}


#endif //MQTT_LOGGER_H
