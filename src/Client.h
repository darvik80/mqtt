//
// Created by Ivan Kishchenko on 19.09.2020.
//

#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace mqtt {
    struct ClientProperties {
        std::string address;
        int port;
    };

    class Client {
    private:
        boost::asio::io_service& _service;
        boost::asio::ip::tcp::endpoint _endpoint;
        boost::asio::ip::tcp::socket _socket;
    public:
        Client(boost::asio::io_service &service, const ClientProperties& props);
    private:
        void onConnect(const boost::system::error_code& err);
    };

}


#endif //MQTT_CLIENT_H
