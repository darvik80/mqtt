//
// Created by Kishchenko, Ivan on 9/16/20.
//

#ifndef MQTT_DECODERFIXTURE_H
#define MQTT_DECODERFIXTURE_H

#include "Decoder.h"
#include <boost/test/unit_test.hpp>


class DecoderFixture {
public:
    mqtt::Decoder decoder;
};


#endif //MQTT_DECODERFIXTURE_H
