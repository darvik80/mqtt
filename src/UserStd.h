//
// Created by Ivan Kishchenko on 26.09.2020.
//

#ifndef MQTT_USERSTD_H
#define MQTT_USERSTD_H

#include <vector>
#include <boost/asio/io_service.hpp>
#include <memory>

namespace mqtt {
    typedef std::vector<uint8_t> ByteBuffer;
    typedef boost::asio::streambuf StreamBuf;

    typedef boost::asio::ip::tcp::endpoint TcpEndpoint;
    typedef boost::asio::ip::tcp::socket TcpSocket;


    typedef boost::asio::io_service IoService;
    typedef std::shared_ptr<IoService> IoServicePtr;
    typedef boost::asio::signal_set SignalSet;
    typedef boost::asio::deadline_timer DeadlineTimer;
    typedef std::shared_ptr<DeadlineTimer> DeadlineTimerPtr;
    typedef std::unique_ptr<DeadlineTimer> DeadlineTimerAutoPtr;

    // Time
    typedef boost::system::error_code ErrorCode;
    typedef boost::posix_time::ptime PosixTime;
    typedef boost::posix_time::time_duration PosixDuration;
    typedef boost::posix_time::seconds PosixSeconds;
    typedef boost::posix_time::microseconds PosixMicroseconds;


}


#endif //MQTT_USERSTD_H
