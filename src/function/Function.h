//
// Created by Ivan Kishchenko on 12.09.2020.
//

#ifndef MQTT_FUNCTION_H
#define MQTT_FUNCTION_H

namespace mqtt::function {
    template<typename T, typename R>
    class Function {
    public:
        virtual R apply(const T &t) = 0;
    };
}


#endif //MQTT_FUNCTION_H
