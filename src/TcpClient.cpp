//
// Created by Ivan Kishchenko on 26.09.2020.
//

#include "TcpClient.h"

#include <iostream>

namespace mqtt {

    TcpClient::TcpClient(boost::asio::io_service &service, const std::string &address, int port)
            : _socket(service), _deadline(service, boost::posix_time::seconds(10)),
              _endpoint(boost::asio::ip::address::from_string(address), port), _inc(512) {
        startConnect();
    }

    void TcpClient::startConnect() {
        _socket.async_connect(_endpoint, [this](const boost::system::error_code &err) {
            if (!_socket.is_open() || err) {
                if (!_socket.is_open()) {
                    std::cout << "Connect timed out\n";
                } else {
                    std::cout << "Connect error: " << err.message() << "\n";
                    _socket.close();
                }

                _deadline.expires_at(_deadline.expires_at() + boost::posix_time::seconds(10));
                _deadline.async_wait([this](const boost::system::error_code &err) {
                    startConnect();
                });
            } else {
                this->onConnect(err);
            }
        });
    }


    void TcpClient::startRead() {
        _socket.async_read_some(
                boost::asio::buffer(_incBuf),
                [this](const boost::system::error_code &err, std::size_t size) {
                    this->onRead(err, size);
                }
        );
    }

    void TcpClient::onConnect(const boost::system::error_code &err) {
        std::cout << "Connected!" << std::endl;
        startRead();
    }

    void TcpClient::onRead(const boost::system::error_code &err, std::size_t size) {
        std::string data((char *) _incBuf.data(), size);

        _out.sputn((const char *) _incBuf.data(), size);

        std::cout << data;

        boost::asio::async_write(_socket, _out, [this](const boost::system::error_code &err, std::size_t size) {
            this->onWrite(err, size);
        });

        startRead();
    }

    void TcpClient::onWrite(const boost::system::error_code &err, std::size_t size) {

    }
}
