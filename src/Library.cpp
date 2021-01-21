//
// Created by Ivan Kishchenko on 24.12.2020.
//

#include "Library.h"
#include "UserStd.h"
#include "logging/Logger.h"

namespace mqtt {

    void Library::init() {
        _factory = std::make_shared<Factory>();

        _timer = Timer::create([this]() {
            MQTT_LOG(debug) << "[Lib] service is alive";
        }, PosixSeconds{5});
        _thread = std::make_shared<std::thread>(Library::run);
        MQTT_LOG(info) << "[Lib] service initialized";
    }

    void Library::run() {
        MQTT_LOG(info) << "[Lib] service thread start";
        IoServiceHolder::get_mutable_instance().run();
        MQTT_LOG(info) << "[Lib] service thread stop";
    }

    void Library::shutdown() {
        _timer.reset();
        IoServiceHolder::get_mutable_instance().stop();
        _thread->join();
        MQTT_LOG(info) << "[Lib] service destroyed";
    }

    Factory::Ptr Library::getFactory() {
        return _factory;
    }
}