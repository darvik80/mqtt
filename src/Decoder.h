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
        virtual message::Message::Ptr decodeConnect(std::istream &inc);

        virtual message::Message::Ptr decodeConnAck(std::istream &inc);

        virtual message::Message::Ptr decodePublish(std::istream &inc);

        virtual message::Message::Ptr decodePubAck(std::istream &inc);

        virtual message::Message::Ptr decodePubRec(std::istream &inc);

        virtual message::Message::Ptr decodePubRel(std::istream &inc);

        virtual message::Message::Ptr decodePubComp(std::istream &inc);

        virtual message::Message::Ptr decodeSubscribe(std::istream &inc);

        virtual message::Message::Ptr decodeSubAck(std::istream &inc);

        virtual message::Message::Ptr decodeUnSubscribe(std::istream &inc);

        virtual message::Message::Ptr decodeUnSubAck(std::istream &inc);

        virtual message::Message::Ptr decodePingReq(std::istream &inc);

        virtual message::Message::Ptr decodePingResp(std::istream &inc);

        virtual message::Message::Ptr decodeDisconnect(std::istream &inc);

    public:
        virtual message::Message::Ptr decode(boost::asio::streambuf &buf);

    };

}

#endif //MQTT_DECODER_H
