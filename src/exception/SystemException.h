//
// Created by Ivan Kishchenko on 26.09.2020.
//

#ifndef MQTT_SYSTEMEXCEPTION_H
#define MQTT_SYSTEMEXCEPTION_H


#include <exception>
#include <boost/system/error_code.hpp>
#include "Exception.h"

namespace mqtt::exception {
    class SystemException : public Exception, public std::exception_ptr {
    private:
        const boost::system::error_code _errorCode;
        const std::string _message;
    public:
        explicit SystemException(const boost::system::error_code &errorCode)
        : _errorCode(errorCode), _message(errorCode.message())
        {
        }

        [[nodiscard]] const char *what() const _NOEXCEPT override {
            return _message.c_str();
        }
    };

}

#endif //MQTT_SYSTEMEXCEPTION_H
