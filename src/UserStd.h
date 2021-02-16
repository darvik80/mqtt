//
// Created by Ivan Kishchenko on 26.09.2020.
//
#pragma once

#ifndef MQTT_USERSTD_H
#define MQTT_USERSTD_H

#define BOOST_THREAD_PROVIDES_FUTURE
#define BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION

#include <boost/thread/future.hpp>

#include <vector>
#include <memory>
#include <boost/serialization/singleton.hpp>
#include <boost/asio.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/signals2.hpp>

#include <boost/thread/lockable_adapter.hpp>
#include <boost/thread/strict_lock.hpp>
#include <boost/thread/with_lock_guard.hpp>

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

    // Time
    typedef boost::system::error_code ErrorCode;
    typedef boost::posix_time::ptime PosixTime;
    typedef boost::posix_time::time_duration PosixDuration;
    typedef boost::posix_time::seconds PosixSeconds;
    typedef boost::posix_time::millisec PosixMilliseconds;
    typedef boost::posix_time::microseconds PosixMicroseconds;

    typedef boost::serialization::singleton<IoService> IoServiceHolder;

    typedef const std::function<void()> Runnable;

    typedef std::function<void(const ByteBuffer &)> DataCallback;

    // Signals
    typedef boost::signals2::connection SignalConnection;

    typedef boost::promise<void> VoidPromise;
    typedef boost::future<void> VoidFuture;
}

#endif //MQTT_USERSTD_H
