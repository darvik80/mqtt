//
// Created by Kishchenko, Ivan on 11/30/20.
//

#ifndef MQTT_CONNECTIONPROPERTIES_H
#define MQTT_CONNECTIONPROPERTIES_H

#include <string>

namespace mqtt::properties {

        struct ConnectionProperties {
            std::string address;
            int port;

            std::string username;
            std::string password;

            std::string clienName;
        };

    }

#endif //MQTT_CONNECTIONPROPERTIES_H
