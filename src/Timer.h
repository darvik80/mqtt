//
// Created by Ivan Kishchenko on 19.12.2020.
//

#ifndef MQTT_TIMER_H
#define MQTT_TIMER_H

#include "UserStd.h"
#include "Component.h"

namespace mqtt {

    class Timer : public Component {
    public:
        typedef std::shared_ptr<Timer> Ptr;
        typedef std::unique_ptr<Timer> AutoPtr;
    private:
        const Runnable _callback;
        const PosixDuration _duration;
        DeadlineTimer _timer;
    public:
        Timer(std::string_view name, const Runnable &callback, const PosixDuration &duration);

        void reset();
        void cancel();

        virtual ~Timer();
    };
}


#endif //MQTT_TIMER_H
