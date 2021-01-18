//
// Created by Ivan Kishchenko on 20.12.2020.
//

#ifndef MQTT_EVENTMANAGER_H
#define MQTT_EVENTMANAGER_H

#include <unordered_set>
#include "EventNetwork.h"
#include "EventTopic.h"
#include "EventHandler.h"
#include <boost/signals2.hpp>
#include <unordered_map>

namespace mqtt {

    class EventManager {
    public:
        typedef std::shared_ptr<EventManager> Ptr;
        typedef boost::signals2::signal<void(const Event &)> Signal;
    private:
        std::unordered_map<std::type_index, Signal> _signals;
    public:
        template<class E>
        void subscribe(const EventHandler::Ptr &handler) {
            auto *channel = dynamic_cast< TEventHandler<E> *>(handler.get());
            if (!channel) {
                throw std::invalid_argument(std::string("Handler not support event ") + typeid(E).name());
            }

            auto &signal = _signals[typeid(E)];
            signal.connect(boost::signals2::signal<void(const Event &)>::slot_type(
                    [channel](const Event &event) {
                        const auto *real = static_cast<const E *>(&event);
                        if (real) {
                            channel->onEvent(*real);
                        }
                    }
            ).track_foreign(handler));
        }

        template<class E>
        SignalConnection subscribe(const std::function<bool(const E &)> &callback) {
            auto &signal = _signals[typeid(E)];
            return signal.connect_extended(
                    [callback](const boost::signals2::connection &conn, const Event &event) {
                        const auto *real = static_cast<const E *>(&event);
                        if (!callback(*real)) {
                            conn.disconnect();
                        }
                    }
            );
        }

        void raiseEvent(const Event &event);
    };
}

#endif //MQTT_EVENTMANAGER_H
