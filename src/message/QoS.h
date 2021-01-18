//
// Created by Ivan Kishchenko on 26.12.2020.
//

#ifndef MQTT_QOS_H
#define MQTT_QOS_H

namespace mqtt::message  {
    enum QoS {
        QOS_AT_MOST_ONCE,
        QOS_AT_LEAST_ONCE,
        QOS_EXACTLY_ONCE,
    };

}

#endif //MQTT_QOS_H
