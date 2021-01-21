//
// Created by Ivan Kishchenko on 24.12.2020.
//

#ifndef MQTT_LIBRARY_H
#define MQTT_LIBRARY_H

#include <thread>
#include "Timer.h"
#include "Factory.h"

namespace mqtt {

    class Library {
    private:
        std::shared_ptr<std::thread> _thread;

        Timer::Ptr _timer;

        Factory::Ptr _factory;
    private:
        static void run();
    public:
        void init();

        Factory::Ptr getFactory();

        void shutdown();
    };
}


#endif //MQTT_LIBRARY_H
