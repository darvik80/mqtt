#include <iostream>

#include <boost/asio.hpp>
#include "Client.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
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
    mqtt::Client clientO(service, properties);
    service.run();
    return 0;
}
