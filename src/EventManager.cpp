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
                    [channelActive](const EventChannelActive &event) {
                        channelActive->onEvent(event);
                    }
            ).track_foreign(subscriber));
        }
        auto *channelInactive = dynamic_cast< EventChannelInactiveSubscriber *>(subscriber.get());
        if (channelInactive) {
            _signalInactive.connect(signals2::signal<void(const EventChannelInactive &)>::slot_type(
                    [channelInactive](const EventChannelInactive &event) {
                        channelInactive->onEvent(event);
                    }
            ).track_foreign(subscriber));
        }
        auto *channelMessage = dynamic_cast< EventChannelMessageSubscriber *>(subscriber.get());
        if (channelMessage) {
            _signalMsg.connect(signals2::signal<void(const EventChannelMessage &)>::slot_type(
                    [channelMessage](const EventChannelMessage &event) {
                        channelMessage->onEvent(event);
                    }
            ).track_foreign(subscriber));
        }
    }

    SignalConnection EventManager::subscribe(const std::function<bool(const Event&)> &callback) {
        auto conn = _signalEvent.connect_extended(
                [callback](const boost::signals2::connection &conn, const Event &event)  {
                    if (!callback(event)) {
                        conn.disconnect();
                    }
                }
        );

        dump();

        return conn;
    }

    void EventManager::raiseEvent(EventChannelActive event) {
        _signalActive(event);
        isChannelActive = true;
        _signalEvent(event);

        dump();
    }

    void EventManager::raiseEvent(EventChannelInactive event) {
        _signalInactive(event);
        _signalEvent(event);
        _signalMsg.disconnect_all_slots();
        _signalEvent.disconnect_all_slots();
        isChannelActive = false;

        dump();
    }

    void EventManager::raiseEvent(const EventChannelMessage &event) {
        _signalMsg(event);
        _signalEvent(event);
        dump();
    }

    void EventManager::dump() {
        MQTT_LOG(info) << "[---";
        MQTT_LOG(info) << "Channel active - slots count: " << _signalActive.num_slots();
        MQTT_LOG(info) << "Channel message - slots count: " << _signalMsg.num_slots();
        MQTT_LOG(info) << "Channel inactive - slots count: " << _signalInactive.num_slots();
        MQTT_LOG(info) << "---]";
    }
}
