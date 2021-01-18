//
// Created by Ivan Kishchenko on 19.12.2020.
//

#include "Timer.h"
#include "logging/Logger.h"


namespace mqtt {
    Timer::Timer(std::string_view name, const Runnable &callback, const PosixDuration &duration)
            : Component(name), _timer(IoServiceHolder::get_mutable_instance()), _callback(callback),
              _duration(duration) {

    }

    Timer::Timer(std::string_view name, const Runnable &callback, const Runnable &cancel, const PosixDuration &duration)
            : Component(name), _timer(IoServiceHolder::get_mutable_instance()), _callback(callback), _cancel(cancel),
              _duration(duration) {

    }


    void Timer::reset() {
        _timer.expires_from_now(_duration);
        _timer.async_wait([this](const ErrorCode &err) {
            if (!err) {
                _callback();
                reset();
            } else {
                MQTT_LOG(debug) << "Timer " << name() << " canceled";
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