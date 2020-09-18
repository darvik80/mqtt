//
// Created by Ivan Kishchenko on 12.09.2020.
//

#ifndef MQTT_ENCODER_H
#define MQTT_ENCODER_H

#include <boost/asio/streambuf.hpp>
#include "message/ConnectMessage.h"
#include <message/ConnAckMessage.h>
#include <message/PublishMessage.h>
#include <message/PubAckMessage.h>
#include <message/PubRelMessage.h>
#include <message/PubRecMessage.h>
#include <message/PubCompMessage.h>
#include <message/SubscribeMessage.h>
#include <message/SubAckMessage.h>
#include <message/UnSubscribeMessage.h>
#include <message/UnSubAckMessage.h>
#include <message/PingReqMessage.h>
#include <message/PingRespMessage.h>
#include <message/DisconnectMessage.h>
#include "message/Message.h"
#include <ostream>

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
        virtual int encodeSubAck(std::ostream &out, const message::SubAckMessage& message);
        virtual int encodeUnSubscribe(std::ostream &out, const message::UnSubscribeMessage& message);
        virtual int encodeUnSubAck(std::ostream &out, const message::UnSubAckMessage& message);
        virtual int encodePingReq(std::ostream &out, const message::PingReqMessage& message);
        virtual int encodePingResp(std::ostream &out, const message::PingRespMessage& message);
        virtual int encodeDisconnect(std::ostream &out, const message::DisconnectMessage& message);
    public:
        virtual void encode(boost::asio::streambuf &buf, std::unique_ptr<message::Message> (*supplier)());
    };

}


#endif //MQTT_ENCODER_H
