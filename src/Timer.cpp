//
// Created by Ivan Kishchenko on 19.12.2020.
//

#include "Timer.h"
#include "logging/Logger.h"


namespace mqtt {
    Timer::Timer(const Runnable &callback, const PosixDuration &duration)
            : _timer(IoServiceHolder::get_mutable_instance()), _callback(callback),
              _duration(duration) {

    }

    Timer::Timer(const Runnable &callback, const Runnable &cancel, const PosixDuration &duration)
            : _timer(IoServiceHolder::get_mutable_instance()), _callback(callback), _cancel(cancel),
              _duration(duration) {

    }


    void Timer::reset() {
        auto weak = weak_from_this();

        auto id = (unsigned long)(this);
        MQTT_LOG(debug) << "[Timer] " << id << " set " << _duration.seconds() << "s";
        _timer.expires_from_now(_duration);
        _timer.async_wait([weak, id](const ErrorCode &err) {
            if (!err) {
                MQTT_LOG(debug) << "[Timer] " << id << " happens";
                auto self = weak.lock();
                if (self) {
                    self->_callback();
                    self->reset();
                }
            } else {
                MQTT_LOG(debug) << "[Timer] " << id << " canceled";
            }
        });
    }

    void Timer::cancel() {
        _timer.cancel();
        if (_cancel) {
            _cancel();
        }
    }

    Timer::~Timer() {
        _timer.cancel();
    };
}