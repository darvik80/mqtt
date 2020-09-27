//
// Created by Ivan Kishchenko on 27.09.2020.
//

#ifndef MQTT_TIMER_H
#define MQTT_TIMER_H


#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_service.hpp>

namespace mqtt {

    class Timer {
    public:
        typedef std::shared_ptr<Timer> Ptr;
        typedef std::unique_ptr<Timer> AutoPtr;

    private:
        boost::posix_time::seconds _seconds;
        boost::asio::deadline_timer _timer;
        std::function<void()> _callback;
    private:
        void onTimer(const boost::system::error_code& err);
    public:
        explicit Timer(boost::asio::io_service &service, int seconds, std::function<void()> callback);
        ~Timer();
    };

}

#endif //MQTT_TIMER_H
