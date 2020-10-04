#include <iostream>

#include <boost/asio.hpp>
#include "Client.h"

#include "logging/Logger.h"
#include "IdleStateHandler.h"
#include "Session.h"
#include "Consumer.h"
#include "Producer.h"

using namespace mqtt;

int main() {
    mqtt::logging::LoggerProperties logProps {boost::log::trivial::debug, true, true, "mqtt.log"};
    mqtt::logging::Logger::init(logProps);

    MQTT_LOG(info) << "Hello world!!!";

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
    auto handler = std::make_shared<mqtt::IdleStateHandler>(0, 0, 5, [&client](mqtt::IdleStateHandler::IdleType idleType) {
        client.write(std::make_shared<mqtt::message::PingReqMessage>(), [](const FutureErrorCode& errCode) { });
    });
    client.getPipeline().addFirst("idle", handler);

    //Session session(std::vector<>{"/test"});
    auto consumer = std::make_shared<DefaultConsumer>();
    consumer->subscribe("/test/*", 0, [](const message::PublishMessage* msg) -> uint32_t {
        std::string data((const char*)msg->getMessage().data(), msg->getMessage().size());
        MQTT_LOG(info) << "onData: " << data;

        return 0;
    });
    client.getPipeline().addLast("consumer", consumer);

    auto producer = std::make_shared<DefaultProducer>(client);

    Timer timer(service, 20, [producer]() {
        producer->publish("/test/*", "Hello World");
    });
    service.run();
    return 0;
}
