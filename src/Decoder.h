//
// Created by Kishchenko, Ivan on 9/16/20.
//

#ifndef MQTT_DECODER_H
#define MQTT_DECODER_H

#include <boost/asio/streambuf.hpp>
#include <message/Message.h>
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
#include <istream>

namespace mqtt {

    class Decoder {
    private:
        virtual std::unique_ptr<message::ConnectMessage> decodeConnect(std::istream &inc);
        virtual std::unique_ptr<message::ConnAckMessage> decodeConnAck(std::istream &inc);
        virtual std::unique_ptr<message::PublishMessage> decodePublish(std::istream &inc);
        virtual std::unique_ptr<message::PubAckMessage> decodePubAck(std::istream &inc);
        virtual std::unique_ptr<message::PubRecMessage> decodePubRec(std::istream &inc);
        virtual std::unique_ptr<message::PubRelMessage> decodePubRel(std::istream &inc);
        virtual std::unique_ptr<message::PubCompMessage> decodePubComp(std::istream &inc);
        virtual std::unique_ptr<message::SubscribeMessage> decodeSubscribe(std::istream &inc);
        virtual std::unique_ptr<message::SubAckMessage> decodeSubAck(std::istream &inc);
        virtual std::unique_ptr<message::UnSubscribeMessage> decodeUnSubscribe(std::istream &inc);
        virtual std::unique_ptr<message::UnSubAckMessage> decodeUnSubAck(std::istream &inc);
        virtual std::unique_ptr<message::PingReqMessage> decodePingReq(std::istream &inc);
        virtual std::unique_ptr<message::PingRespMessage> decodePingResp(std::istream &inc);
        virtual std::unique_ptr<message::DisconnectMessage> decodeDisconnect(std::istream &inc);
    public:
        virtual void decode(boost::asio::streambuf &buf, void (*consumer)(const mqtt::message::Message&));

    };

}

#endif //MQTT_DECODER_H
