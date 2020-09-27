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

    typedef std::shared_ptr<boost::asio::io_service> ServicePtr;
}


#endif //MQTT_USERSTD_H
