//
// Created by Ivan Kishchenko on 20.12.2020.
//

#ifndef MQTT_EVENTMANAGER_H
#define MQTT_EVENTMANAGER_H

#include <unordered_set>
#include "Event.h"
#include "logging/Logger.h"
#include <boost/signals2.hpp>

namespace mqtt {

    class EventSubscriber {
    public:
        typedef std::shared_ptr<EventSubscriber> Ptr;
        virtual ~EventSubscriber() = default;
    };

    class EventChannelActiveSubscriber : virtual public EventSubscriber {
    public:
        virtual void onEvent(const EventChannelActive &event) = 0;
    };

    class EventChannelInactiveSubscriber : virtual public EventSubscriber {
    public:
        virtual void onEvent(const EventChannelInactive &event) = 0;
    };

    class EventChannelMessageSubscriber : virtual public EventSubscriber {
    public:
        virtual void onEvent(const EventChannelMessage &event) = 0;
    };

    class DefaultEventChannelSubscriber : public EventChannelActiveSubscriber, public EventChannelInactiveSubscriber, public EventChannelMessageSubscriber {
    public:
        void onEvent(const EventChannelActive &event) override {
            MQTT_LOG(info) << "Handle channel active";
        }

        void onEvent(const EventChannelInactive &event) override {
            MQTT_LOG(info) << "Handle channel inactive";
        }

        void onEvent(const EventChannelMessage &event) override {
            MQTT_LOG(info) << "Handle channel message: " << event.getMessage()->getTypeStr();
        }
    };

    class EventManager {
    private:
        bool isChannelActive{false};
        boost::signals2::signal<void(const EventChannelActive &)> _signalActive;
        boost::signals2::signal<void(const EventChannelInactive &)> _signalInactive;
        boost::signals2::signal<void(const EventChannelMessage &)> _signalMsg;


        boost::signals2::signal<void(const Event &)> _signalEvent;

    private:
        void dump();
    public:
        void subscribe(EventSubscriber::Ptr &subscriber);

        SignalConnection subscribe(const std::function<bool(const Event&)>& callback);

        void raiseEvent(EventChannelActive event);

        void raiseEvent(EventChannelInactive event);

        void raiseEvent(const EventChannelMessage& event);
    };

}

#endif //MQTT_EVENTMANAGER_H
