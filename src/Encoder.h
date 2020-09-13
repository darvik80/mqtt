//
// Created by Ivan Kishchenko on 12.09.2020.
//

#ifndef MQTT_ENCODER_H
#define MQTT_ENCODER_H

#include <boost/asio/streambuf.hpp>
#include <message/ConnAckMessage.h>
#include <message/PublishMessage.h>
#include <message/PubAckMessage.h>
#include <message/PubRelMessage.h>
#include <message/PubRecMessage.h>
#include <message/PubCompMessage.h>
#include <message/SubscribeMessage.h>
#include "function/Supplier.h"
#include "message/Message.h"
#include "message/ConnectMessage.h"

namespace mqtt {
    class Encoder {
    private:
        virtual int encodeConnect(std::ostream &out, const message::ConnectMessage& message);
        virtual int encodeConnAck(std::ostream &out, const message::ConnAckMessage& message);
        virtual int encodePublish(std::ostream &out, const message::PublishMessage& message);
        virtual int encodePubAck(std::ostream &out, const message::PubAckMessage& message);
        virtual int encodePubRec(std::ostream &out, const message::PubRecMessage& message);
        virtual int encodePubRel(std::ostream &out, const message::PubRelMessage& message);
        virtual int encodePubComp(std::ostream &out, const message::PubCompMessage& message);
        virtual int encodeSubscribe(std::ostream &out, const message::SubscribeMessage& message);
    public:
        virtual void encode(boost::asio::streambuf &buf, function::Supplier<message::Message::MessagePtr>& consumer);
    };

}


#endif //MQTT_ENCODER_H
