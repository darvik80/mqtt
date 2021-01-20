//
// Created by Kishchenko, Ivan on 1/18/21.
//

#ifndef MQTT_EVENTSYSTEM_H
#define MQTT_EVENTSYSTEM_H

#include "Event.h"

namespace mqtt {

    class EventTimeout : public Event {
    public:
        explicit EventTimeout()
                : Event(ErrorCode{boost::asio::error::timed_out}) {}
    };

}


#endif //MQTT_EVENTSYSTEM_H
