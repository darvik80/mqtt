//
// Created by Ivan Kishchenko on 27.09.2020.
//

#include "Timer.h"
#include <iostream>

namespace mqtt {
    Timer::Timer(boost::asio::io_service &service, int seconds, std::function<void()> callback)
            : _seconds(seconds), _timer(service, boost::posix_time::seconds(seconds)), _callback(callback) {
        _timer.async_wait([this](const boost::system::error_code& err) { this->onTimer(err); });
    }

    void Timer::onTimer(const boost::system::error_code& err) {
        if (err) {
            std::cout << err.message() << std::endl;
        } else {
            _callback();
        }
    }

    Timer::~Timer() {
        _timer.cancel();
    }
}
