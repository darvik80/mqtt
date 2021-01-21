//
// Created by Ivan Kishchenko on 20.12.2020.
//

#include "EventManager.h"

#include "logging/Logger.h"


using namespace boost;

namespace mqtt {

    void EventManager::raiseEvent(const Event &event) {
        auto iter = _signals.find(typeid(event));
        if (iter != _signals.end()) {
            MQTT_LOG(debug) << "[EM] raise: " << iter->first.name() << " subs: " << iter->second.num_slots() << std::endl;
            iter->second(event);
        } else {
            MQTT_LOG(warning) << "[EM] missed: " << typeid(event).name() << std::endl;
        }

    }
}
