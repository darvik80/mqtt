//
// Created by Ivan Kishchenko on 24.12.2020.
//

#include "Library.h"
#include "UserStd.h"
#include "logging/Logger.h"

namespace mqtt {

    void Library::init() {
        _factory = std::make_shared<Factory>();

        _timer = std::make_shared<Timer>("Library Timer", [this]() {
            MQTT_LOG(debug) << "Library is alive";
            _timer->reset();
        }, PosixSeconds{5});
        _timer->reset();
        _thread = std::make_shared<std::thread>([this]() {
            this->run();
        });
        MQTT_LOG(info) << "Library initialized";
    }

    void Library::run() {
        MQTT_LOG(info) << "Library thread start";
        IoServiceHolder::get_mutable_instance().run();
        MQTT_LOG(info) << "Library thread stop";
    }

    void Library::shutdown() {
        _timer.reset();
        IoServiceHolder::get_mutable_instance().stop();
        _thread->join();
        MQTT_LOG(info) << "Library destroyed";
    }

    Factory::Ptr Library::getFactory() {
        return _factory;
    }
}