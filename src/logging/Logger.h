//
// Created by Kishchenko, Ivan on 10/2/20.
//

#ifndef MQTT_LOGGER_H
#define MQTT_LOGGER_H

#include <boost/log/trivial.hpp>

#define MQTT_LOG(level)  BOOST_LOG_TRIVIAL(level)

namespace mqtt::logging {

class Logger {
public:
    static void init();
};

}


#endif //MQTT_LOGGER_H
