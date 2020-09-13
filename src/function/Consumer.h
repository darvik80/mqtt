//
// Created by Ivan Kishchenko on 12.09.2020.
//

#ifndef MQTT_CONSUMER_H
#define MQTT_CONSUMER_H

namespace mqtt::function {

    template <typename T>
    class Consumer {
    public:
        virtual void apply(const T& t) = 0;
    };

}


#endif //MQTT_CONSUMER_H
