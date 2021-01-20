//
// Created by Ivan Kishchenko on 25.12.2020.
//

#ifndef MQTT_EVENTHANDLER_H
#define MQTT_EVENTHANDLER_H

#include <memory>
#include "EventNetwork.h"
#include "EventTopic.h"

namespace mqtt {

    class EventHandler {
    public:
        typedef std::shared_ptr<EventHandler> Ptr;

        virtual ~EventHandler() = default;
    };

    template<class T>
    class TEventHandler : virtual public EventHandler {
    public:
        virtual void onEvent(const T &event) = 0;

        ~TEventHandler() override = default;
    };

    class EventChannelActiveHandler : virtual public TEventHandler<EventChannelActive> {
    public:
        void onEvent(const EventChannelActive &event) override = 0;
    };

    class EventChannelInactiveHandler : virtual public TEventHandler<EventChannelInactive> {
    public:
        void onEvent(const EventChannelInactive &event) override = 0;
    };

    class EventChannelMessageHandler : virtual public TEventHandler<EventChannelMessage> {
    public:
        void onEvent(const EventChannelMessage &event) override = 0;
    };

    class EventTopicSubscribeHandler : virtual public TEventHandler<EventTopicSubscribe> {
    public:
        void onEvent(const EventTopicSubscribe &event) override = 0;
    };

    class EventTopicUnSubscribeHandler : virtual public TEventHandler<EventTopicUnSubscribe> {
    public:
        void onEvent(const EventTopicUnSubscribe &event) override = 0;
    };

    template<class T>
    class EventHandlerWrapper : public TEventHandler<T> {
        std::function<void(const T &)> _handler;
    public:
        explicit EventHandlerWrapper(std::function<void(const T &)> handler) : _handler(std::move(handler)) {
        }

        void onEvent(const T &event) override {
            _handler(event);
        }
    };
}

#endif //MQTT_EVENTHANDLER_H
