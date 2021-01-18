//
// Created by Ivan Kishchenko on 05.09.2020.
//

#ifndef MQTT_READERFIXTURE_H
#define MQTT_READERFIXTURE_H

#include <boost/test/unit_test.hpp>
#include "Reader.h"

class ReaderFixture {
public:
    mqtt::Reader _decoder;
};


#endif //MQTT_READERFIXTURE_H
