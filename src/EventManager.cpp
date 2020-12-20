//
// Created by Ivan Kishchenko on 20.12.2020.
//

#include "EventManager.h"

using namespace boost;

namespace mqtt {

    void EventManager::subscribe(mqtt::EventSubscriber::Ptr &subscriber) {
        auto *channelActive = dynamic_cast< EventChannelActiveSubscriber *>(subscriber.get());
        if (channelActive) {
            _signalActive.connect(signals2::signal<void(const EventChannelActive &)>::slot_type(
                    [channelActive](const EventChannelActive& event) {
                        channelActive->onEvent(event);
                    }
            ).track_foreign(subscriber));
        }
        auto *channelInactive = dynamic_cast< EventChannelInactiveSubscriber *>(subscriber.get());
        if (channelInactive) {
            _signalInactive.connect(signals2::signal<void(const EventChannelInactive &)>::slot_type(
                    [channelInactive](const EventChannelInactive& event) {
                        channelInactive->onEvent(event);
                    }
            ).track_foreign(subscriber));
        }
        auto *channelMessage = dynamic_cast< EventChannelMessageSubscriber *>(subscriber.get());
        if (channelMessage) {
            _signalMsg.connect(signals2::signal<void(const EventChannelMessage &)>::slot_type(
                    [channelMessage](const EventChannelMessage& event) {
                        channelMessage->onEvent(event);
                    }
            ).track_foreign(subscriber));
        }
    }

    void EventManager::raiseEvent(EventChannelActive event) {
        MQTT_LOG(info) << "Channel active - slots count: " << _signalActive.num_slots();
        _signalActive(event);
    }

    void EventManager::raiseEvent(EventChannelInactive event) {
        MQTT_LOG(info) << "Channel inactive - slots count: " << _signalInactive.num_slots();
        _signalInactive(event);
    }

    void EventManager::raiseEvent(const EventChannelMessage& event) {
        MQTT_LOG(info) << "Channel message - slots count: " << _signalMsg.num_slots();
        _signalMsg(event);
    }
}
