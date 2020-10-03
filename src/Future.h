//
// Created by Kishchenko, Ivan on 9/30/20.
//

#ifndef MQTT_FUTURE_H
#define MQTT_FUTURE_H

#include <exception/Exception.h>
#include <boost/system/error_code.hpp>

namespace mqtt {

    class Future {
    public:
        virtual bool isDone() const = 0;

        virtual bool isSuccess() const = 0;

        virtual bool isCancelled() const = 0;

        virtual exception::Exception::Ptr cause() const = 0;
    };

    class SystemFuture : public Future {
    private:
        exception::Exception::Ptr _exception;

    public:
        explicit SystemFuture(const boost::system::error_code &errorCode) {}

        [[nodiscard]] bool isDone() const override {
            return true;
        }

        [[nodiscard]] bool isSuccess() const override {
            return _exception == nullptr;
        }

        [[nodiscard]] bool isCancelled() const override {
            return false;
        }

        [[nodiscard]] exception::Exception::Ptr cause() const override {
            return _exception;
        }
    };
}


#endif //MQTT_FUTURE_H
