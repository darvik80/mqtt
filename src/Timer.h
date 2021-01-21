//
// Created by Ivan Kishchenko on 19.12.2020.
//

#ifndef MQTT_TIMER_H
#define MQTT_TIMER_H

#include "UserStd.h"
#include "Component.h"

namespace mqtt {

    class Timer : public std::enable_shared_from_this<Timer> {
    public:
        typedef std::shared_ptr<Timer> Ptr;
    private:
        const Runnable _callback;
        const Runnable _cancel{nullptr};
        const PosixDuration _duration;
        DeadlineTimer _timer;
    private:
        Timer(const Runnable &callback, const PosixDuration &duration);
        Timer(const Runnable &callback, const Runnable &cancel, const PosixDuration &duration);

    public:
        template<typename ... T>
        static std::shared_ptr<Timer> create(T &&... all) {
            auto res = std::shared_ptr<Timer>(new Timer(std::forward<T>(all)...));
            res->reset();
            return res;
        }

        void reset();

        void cancel();

        virtual ~Timer();
    };
}


#endif //MQTT_TIMER_H
