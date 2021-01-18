#include <iostream>

#include <boost/asio.hpp>

#include "logging/Logger.h"
#include "Library.h"

#include <boost/program_options.hpp>

using namespace mqtt;

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help", "produce help message")
            ("user", po::value<std::string>(), "MQTT login name")
            ("password", po::value<std::string>(), "MQTT password")
            ;
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    properties::LoggerProperties logProps{boost::log::trivial::info, true, true, "mqtt.log"};
    logging::Logger::init(logProps);

    boost::asio::io_service main;
    boost::asio::signal_set signals(main, SIGINT, SIGTERM, SIGQUIT);
    signals.async_wait([](const boost::system::error_code &error, int signalNumber) {
        if (!error) {
            // A signal occurred.
            MQTT_LOG(info) << "Handle: " << signalNumber;
        }
    });

    auto lib = std::make_shared<Library>();
    lib->init();
    auto factory = lib->getFactory();

    properties::ConnectionProperties properties{
            "alicloud.crearts.xyz",
            1883,
            vm["user"].as<std::string>(),
            vm["password"].as<std::string>(),
    };

    DeadlineTimer timer(main);
    timer.expires_from_now(PosixSeconds{10});
    {
        auto client = factory->create(properties);
        auto sub = client->subscribe("/home/new", message::QOS_AT_LEAST_ONCE, [](const ByteBuffer &data) {
            std::string msg((const char *) data.data(), data.size());
            MQTT_LOG(info) << "Got MSG: " << msg;
        });

//        auto pub = client->publisher("/home/test", message::QOS_AT_LEAST_ONCE);
//        timer.async_wait([pub, &timer](const ErrorCode& err) {
//            //sub.shutdown();
//            pub.publish("Hello World");
//        });

        main.run();
    }
    lib->shutdown();
    return 0;
}
