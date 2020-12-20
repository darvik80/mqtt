//
// Created by Kishchenko, Ivan on 9/16/20.
//

#include "Decoder.h"
#include "Reader.h"

using namespace boost;

namespace mqtt {

    message::Message::Ptr Decoder::decode(asio::streambuf &buf) {
        Header header{};
        header.all = buf.sgetc();

        asio::streambuf cache;
        cache.commit(
                buffer_copy(
                        cache.prepare(buf.size()),
                        buf.data()
                )
        );

        std::istream inc(&cache);
        inc.exceptions(std::istream::eofbit | std::istream::badbit);

        message::Message::Ptr ptrMsg;
        switch (header.bits.type) {
            case MQTT_MSG_CONNECT:
                ptrMsg = decodeConnect(inc);
                break;
            case MQTT_MSG_CONNACK:
                ptrMsg = decodeConnAck(inc);
                break;
            case MQTT_MSG_PUBLISH:
                ptrMsg = decodePublish(inc);
                break;
            case MQTT_MSG_PUBACK:
                ptrMsg = decodePubAck(inc);
                break;
            case MQTT_MSG_PUBREC:
                ptrMsg = decodePubRec(inc);
                break;
            case MQTT_MSG_PUBREL:
                ptrMsg = decodePubRel(inc);
                break;
            case MQTT_MSG_PUBCOMP:
                ptrMsg = decodePubComp(inc);
                break;
            case MQTT_MSG_SUBSCRIBE:
                ptrMsg = decodeSubscribe(inc);
                break;
            case MQTT_MSG_SUBACK:
                ptrMsg = decodeSubAck(inc);
                break;
            case MQTT_MSG_UNSUBSCRIBE:
                ptrMsg = decodeUnSubscribe(inc);
                break;
            case MQTT_MSG_UNSUBACK:
                ptrMsg = decodeUnSubAck(inc);
                break;
            case MQTT_MSG_PINGREQ:
                ptrMsg = decodePingReq(inc);
                break;
            case MQTT_MSG_PINGRESP:
                ptrMsg = decodePingResp(inc);
                break;
            case MQTT_MSG_DISCONNECT:
                ptrMsg = decodeDisconnect(inc);
                break;
            default:
                break;
        }

        buf.consume(buf.size() - cache.size());

        return ptrMsg;
    }

    message::Message::Ptr  Decoder::decodeConnect(std::istream &inc) {
        Reader reader;
        auto msg = std::make_shared<message::ConnectMessage>();
        msg->setHeader(reader.readUint8(inc));
        msg->setSize(reader.readVariableInt(inc));

        msg->setProtocolName(reader.readString(inc));
        /// 3.1.2.2 Protocol Level
        msg->setProtocolLevel(reader.readUint8(inc));
        if (msg->getProtocolLevel() != 3) {
            throw;
        }
        /// 3.1.2.3 Connect Flags
        msg->setFlags(reader.readUint8(inc));

        /// 3.1.2.10 Keep Alive
        msg->setKeepAlive(reader.readUint16(inc));
        /// 3.1.3.1 Connection Identifier
        msg->setClientId(reader.readString(inc));

        if (msg->getFlags().bits.willFlag) {
            /// 3.1.3.2 Will Topic
            msg->setWillTopic(reader.readString(inc));
            /// 3.1.3.3 Will Message
            msg->setWillMessage(reader.readString(inc));
        }

        if (msg->getFlags().bits.username) {
            /// 3.1.3.4 User Name
            msg->setUserName(reader.readString(inc));
        }

        if (msg->getFlags().bits.password) {
            /// 3.1.3.5 Password
            msg->setPassword(reader.readString(inc));
        }

        return msg;
    }

    message::Message::Ptr Decoder::decodeConnAck(std::istream &inc) {
        Reader reader;
        auto msg = std::make_shared<message::ConnAckMessage>();

        /// 3.2.1 Fixed header
        msg->setHeader(reader.readUint8(inc));
        msg->setSize(reader.readVariableInt(inc));

        /// 3.2.2 Variable header
        /// 3.2.2.1 Connect Acknowledge Flags
        /// 3.2.2.2 Session Present
        msg->setFlags(reader.readUint8(inc));

        /// 3.2.2.3 Connect Return code
        msg->setReasonCode(reader.readUint8(inc));

        return msg;
    }

    message::Message::Ptr Decoder::decodePublish(std::istream &inc) {
        Reader reader;
        auto msg = std::make_shared<message::PublishMessage>();

        /// 3.2.1 Fixed header
        msg->setHeader(reader.readUint8(inc));
        msg->setSize(reader.readVariableInt(inc));

        /// 3.3.2.1 Topic Name
        msg->setTopic(reader.readString(inc));

        if (msg->getHeader().bits.qos) {
            /// 3.3.2.2 Packet Identifier
            msg->setPacketIdentifier(reader.readInt16(inc));
        }

        msg->setMessage(reader.readRestData(inc));

        return msg;
    }

    message::Message::Ptr  Decoder::decodePubAck(std::istream &inc) {
        Reader reader;
        auto msg = std::make_shared<message::PubAckMessage>();
        /// 3.4.1 Fixed header
        msg->setHeader(reader.readUint8(inc));
        msg->setSize(reader.readVariableInt(inc));

        /// 3.4.2 Variable header
        msg->setPacketIdentifier(reader.readInt16(inc));

        return msg;
    }

    message::Message::Ptr  Decoder::decodePubRec(std::istream &inc) {
        Reader reader;
        auto msg = std::make_shared<message::PubRecMessage>();
        /// 3.5.1 Fixed header
        msg->setHeader(reader.readUint8(inc));
        msg->setSize(reader.readVariableInt(inc));

        /// 3.5.2 Variable header
        msg->setPacketIdentifier(reader.readInt16(inc));

        return msg;

    }

    message::Message::Ptr  Decoder::decodePubRel(std::istream &inc) {
        Reader reader;
        auto msg = std::make_shared<message::PubRelMessage>();
        /// 3.6.1 Fixed header
        msg->setHeader(reader.readUint8(inc));
        msg->setSize(reader.readVariableInt(inc));

        /// 3.6.2 Variable header
        msg->setPacketIdentifier(reader.readInt16(inc));

        return msg;
    }

    message::Message::Ptr  Decoder::decodePubComp(std::istream &inc) {
        Reader reader;
        auto msg = std::make_shared<message::PubCompMessage>();
        /// 3.7.1 Fixed header
        msg->setHeader(reader.readUint8(inc));
        msg->setSize(reader.readVariableInt(inc));

        /// 3.7.2 Variable header
        msg->setPacketIdentifier(reader.readInt16(inc));

        return msg;
    }

    message::Message::Ptr  Decoder::decodeSubscribe(std::istream &inc) {
        Reader reader;
        auto msg = std::make_shared<message::SubscribeMessage>();
        /// 3.8.1 Fixed header
        msg->setHeader(reader.readUint8(inc));
        msg->setSize(reader.readVariableInt(inc));
        uint32_t msgSize = msg->getSize();

        /// 3.8.2.1 Variable header non normative example
        msg->setPacketIdentifier(reader.readInt16(inc));

        /// 3.8.3 Payload
        msgSize -= sizeof(uint16_t);
        while (msgSize > 0) {
            std::string topicFilter = reader.readString(inc);
            uint8_t qos = reader.readUint8(inc);
            msg->addTopic(topicFilter, qos);

            msgSize -= (sizeof(uint16_t) + topicFilter.size() + sizeof(uint8_t));
        }

        return msg;

    }

    message::Message::Ptr Decoder::decodeSubAck(std::istream &inc) {
        Reader reader;
        auto msg = std::make_shared<message::SubAckMessage>();
        /// 3.9.1 Fixed header
        msg->setHeader(reader.readUint8(inc));
        msg->setSize(reader.readVariableInt(inc));

        /// 3.9.2 Variable header
        msg->setPacketIdentifier(reader.readInt16(inc));

        /// 3.9.3 Payload
        msg->setReturnCode(reader.readUint8(inc));

        return msg;

    }

    message::Message::Ptr Decoder::decodeUnSubscribe(std::istream &inc) {
        Reader reader;
        auto msg = std::make_shared<message::UnSubscribeMessage>();
        /// 3.10.1 Fixed header
        msg->setHeader(reader.readUint8(inc));
        msg->setSize(reader.readVariableInt(inc));

        /// 3.10.2 Variable header
        msg->setPacketIdentifier(reader.readInt16(inc));

        /// 3.10.3 Payload
        while (!inc.eof()) {
            msg->addTopicFilter(reader.readString(inc));
        }

        return msg;
    }

    message::Message::Ptr Decoder::decodeUnSubAck(std::istream &inc) {
        Reader reader;
        auto msg = std::make_shared<message::UnSubAckMessage>();
        /// 3.11.1 Fixed header
        msg->setHeader(reader.readUint8(inc));
        msg->setSize(reader.readVariableInt(inc));

        /// 3.11.2 Variable header
        msg->setPacketIdentifier(reader.readInt16(inc));

        return msg;
    }

    message::Message::Ptr Decoder::decodePingReq(std::istream &inc) {
        Reader reader;
        auto msg = std::make_shared<message::PingReqMessage>();
        /// 3.12.1 Fixed header
        msg->setHeader(reader.readUint8(inc));
        msg->setSize(reader.readVariableInt(inc));

        return msg;
    }

    message::Message::Ptr Decoder::decodePingResp(std::istream &inc) {
        Reader reader;
        auto msg = std::make_unique<message::PingRespMessage>();
        /// 3.13.1 Fixed header
        msg->setHeader(reader.readUint8(inc));
        msg->setSize(reader.readVariableInt(inc));

        return msg;
    }

    message::Message::Ptr Decoder::decodeDisconnect(std::istream &inc) {
        Reader reader;
        auto msg = std::make_shared<message::DisconnectMessage>();
        /// 3.14.1 Fixed header
        msg->setHeader(reader.readUint8(inc));
        msg->setSize(reader.readVariableInt(inc));

        return msg;
    }
}