//
// Created by Ivan Kishchenko on 19.09.2020.
//

#include "Client.h"

using namespace boost;
using namespace boost::asio;

namespace mqtt {

    Client::Client(boost::asio::io_service &service, const ClientProperties &props)
            : _service(service), _socket(service), _endpoint(ip::address::from_string(props.address), props.port) {
        _socket.async_connect(_endpoint, [this](const boost::system::error_code &err) {
            this->onConnect(err);
        });
    }

    void Client::onConnect(const boost::system::error_code &err) {
        printf("Connected\r\n");
    }

}