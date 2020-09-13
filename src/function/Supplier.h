//
// Created by Ivan Kishchenko on 12.09.2020.
//

#ifndef MQTT_SUPPLIER_H
#define MQTT_SUPPLIER_H

namespace mqtt::function {

    template<typename R>
    class Supplier {
    public:
        virtual R get() = 0;
    };

}


#endif //MQTT_SUPPLIER_H
