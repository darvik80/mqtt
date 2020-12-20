#include <iostream>

#include <boost/asio.hpp>
#include "Connection.h"

#include "logging/Logger.h"
#include "EventManager.h"

using namespace mqtt;

int main() {
    properties::LoggerProperties logProps{boost::log::trivial::info, true, true, "mqtt.log"};
    logging::Logger::init(logProps);

    boost::asio::signal_set signals(IoServiceHolder::get_mutable_instance(), SIGINT, SIGTERM, SIGQUIT);
    signals.async_wait([](const boost::system::error_code &error, int signalNumber) {
        if (!error) {
            // A signal occurred.
            MQTT_LOG(info) << "Handle: " << signalNumber;
        }
    });

    properties::ConnectionProperties properties{
            "149.129.51.54",
            1883,
            "darvik",
            "Selena123"
    };
    mqtt::Connection client(properties);

    EventSubscriber::Ptr subscriber = std::make_shared<DefaultEventChannelSubscriber>();
    client.getEventManager().subscribe(subscriber);

    IoServiceHolder::get_mutable_instance().run();
    return 0;
}
