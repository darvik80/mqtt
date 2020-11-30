//
// Created by Kishchenko, Ivan on 11/30/20.
//

#ifndef MQTT_CLIENTPROPERTIES_H
#define MQTT_CLIENTPROPERTIES_H

#include <string>

namespace mqtt::properties {

        struct ClientProperties {
            std::string address;
            int port;
        };

    }

#endif //MQTT_CLIENTPROPERTIES_H
