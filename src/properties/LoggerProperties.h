//
// Created by Kishchenko, Ivan on 11/30/20.
//

#ifndef MQTT_LOGGERPROPERTIES_H
#define MQTT_LOGGERPROPERTIES_H

#include <string>
#include <boost/log/trivial.hpp>

namespace mqtt::properties {

    struct LoggerProperties {
        boost::log::trivial::severity_level level;
        bool console;
        bool file;
        std::string fileName;
    };

}


#endif //MQTT_LOGGERPROPERTIES_H
