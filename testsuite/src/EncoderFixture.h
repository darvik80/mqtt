//
// Created by Ivan Kishchenko on 05.09.2020.
//

#ifndef MQTT_ENCODERTEST_H
#define MQTT_ENCODERTEST_H

#define BOOST_TEST_MODULE Mqtt

#include <boost/test/unit_test.hpp>

#include "Writer.h"

class EncoderFixture {
public:
    Encoder _encoder;
};


#endif //MQTT_ENCODERTEST_H
