//
// Created by Ivan Kishchenko on 26.12.2020.
//

#ifndef MQTT_EVENTTOPIC_H
#define MQTT_EVENTTOPIC_H

#include <string>
#include "Event.h"

namespace mqtt {

    class Subscriber;

    class EventTopic : public Event {
    private:
        std::shared_ptr<Subscriber> _subscriber;
        std::string _topic;
    public:
        EventTopic(const std::shared_ptr<Subscriber>& subscriber, std::string_view topic)
                : _subscriber(subscriber), _topic(topic) {}

        [[nodiscard]] const std::shared_ptr<Subscriber> &getSubscriber() const {
            return _subscriber;
        }

        [[nodiscard]] const std::string &getTopic() const {
            return _topic;
        }

    };

    class EventTopicSubscribe : public EventTopic {
    public:
        explicit EventTopicSubscribe(const std::shared_ptr<Subscriber>& subscriber, std::string_view topic)
                : EventTopic(subscriber, topic) {}
    };

    class EventTopicUnSubscribe : public EventTopic {
    public:
        explicit EventTopicUnSubscribe(const std::shared_ptr<Subscriber>& subscriber, std::string_view topic)
                : EventTopic(subscriber, topic) {}
    };
}

#endif //MQTT_EVENTTOPIC_H
