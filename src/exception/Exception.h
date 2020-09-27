//
// Created by Ivan Kishchenko on 26.09.2020.
//

#ifndef MQTT_EXCEPTION_H
#define MQTT_EXCEPTION_H


#include <exception>
#include <memory>

namespace mqtt::exception {
    class Exception : public std::exception {
    public:
        typedef std::shared_ptr<Exception> Ptr;
        typedef std::unique_ptr<Exception> AutoPtr;
    };
}

#endif //MQTT_EXCEPTION_H
