#include <iostream>

#include <boost/asio.hpp>
#include "Client.h"

#include "logging/Logger.h"

int main() {
    mqtt::logging::Logger::init();

    MQTT_LOG(error) << "Hello world!!!";

    boost::asio::io_service service;

    boost::asio::signal_set signals(service, SIGINT, SIGTERM, SIGQUIT);
    signals.async_wait([](const boost::system::error_code &error, int signalNumber) {
        if (!error) {
            // A signal occurred.
            printf("Handle: %d\r\n", signalNumber);
        }
    });

    mqtt::ClientProperties properties{
            "192.168.100.3",
            1883
    };
    mqtt::Client client(service, properties);

    //mqtt::TcpClient tcpClient(service, "127.0.0.1", 5000);
    service.run();
    return 0;
}
