//
// Created by Ivan Kishchenko on 26.09.2020.
//

#ifndef MQTT_TCPCLIENT_H
#define MQTT_TCPCLIENT_H

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio.hpp>

#include <vector>

namespace mqtt {

    class TcpClient {
    private:
        boost::asio::ip::tcp::endpoint _endpoint;
        boost::asio::ip::tcp::socket _socket;

        std::vector<uint8_t> _incBuf;
        boost::asio::streambuf _inc;
        boost::asio::streambuf _out;

        boost::asio::deadline_timer _deadline;
    public:
        TcpClient(boost::asio::io_service &service, const std::string &address, int port);
    private:
        void onConnect(const boost::system::error_code& err);
        void onRead(const boost::system::error_code& err, std::size_t size);
        void onWrite(const boost::system::error_code& err, std::size_t size);

        void startConnect();
        void startRead();
    };

}


#endif //MQTT_TCPCLIENT_H
