//
// Created by Ivan Kishchenko on 12.09.2020.
//

#include "Encoder.h"
#include "Writer.h"

using namespace boost;
using namespace mqtt::message;

namespace mqtt {
    void Encoder::encode(boost::asio::streambuf &buf, Message::Ptr msg) {
        boost::asio::streambuf data;
        std::ostream body(&data);

        int dataSize = 0;
        switch (msg->getType()) {
            case MQTT_MSG_CONNECT:
                dataSize = encodeConnect(body, *(dynamic_cast<message::ConnectMessage*>(msg.get())));
                break;
            case MQTT_MSG_CONNACK:
                dataSize = encodeConnAck(body, *(dynamic_cast<message::ConnAckMessage*>(msg.get())));
                break;
            case MQTT_MSG_PUBLISH:
                dataSize = encodePublish(body, *(dynamic_cast<message::PublishMessage*>(msg.get())));
                break;
            case MQTT_MSG_PUBACK:
                dataSize = encodePubAck(body, *(dynamic_cast<message::PubAckMessage*>(msg.get())));
                break;
            case MQTT_MSG_PUBREC:
                dataSize = encodePubRec(body, *(dynamic_cast<message::PubRecMessage*>(msg.get())));
                break;
            case MQTT_MSG_PUBREL:
                dataSize = encodePubRel(body, *(dynamic_cast<message::PubRelMessage*>(msg.get())));
                break;
            case MQTT_MSG_PUBCOMP:
                dataSize = encodePubComp(body, *(dynamic_cast<message::PubCompMessage*>(msg.get())));
                break;
            case MQTT_MSG_SUBSCRIBE:
                dataSize = encodeSubscribe(body, *(dynamic_cast<message::SubscribeMessage*>(msg.get())));
                break;
            case MQTT_MSG_SUBACK:
                dataSize = encodeSubAck(body, *(dynamic_cast<message::SubAckMessage*>(msg.get())));
                break;
            case MQTT_MSG_UNSUBSCRIBE:
                dataSize = encodeUnSubscribe(body, *(dynamic_cast<message::UnSubscribeMessage*>(msg.get())));
                break;
            case MQTT_MSG_UNSUBACK:
                dataSize = encodeUnSubAck(body, *(dynamic_cast<message::UnSubAckMessage*>(msg.get())));
                break;
            case MQTT_MSG_PINGREQ:
                dataSize = encodePingReq(body, *(dynamic_cast<message::PingReqMessage*>(msg.get())));
                break;
            case MQTT_MSG_PINGRESP:
                dataSize = encodePingResp(body, *(dynamic_cast<message::PingRespMessage*>(msg.get())));
                break;
            case MQTT_MSG_DISCONNECT:
                dataSize = encodeDisconnect(body, *(dynamic_cast<message::DisconnectMessage*>(msg.get())));
                break;
            default:
                throw;

        }

        std::ostream stream(&buf);
        Writer writer;
        writer.writeUint8(msg->getHeader().all, stream);
        writer.writeVariableInt(dataSize, stream);
        stream.write((const char *) data.data().data(), data.size());
    }

    int Encoder::encodeConnect(std::ostream &out, const message::ConnectMessage &message) {
        Writer writer;
        size_t res = 0;

        /// 3.1.2.1 Protocol name
        res += writer.writeString(message.getProtocolName(), out);
        /// 3.1.2.2 Protocol version
        res += writer.writeUint8(message.getProtocolLevel(), out);
        /// 3.1.2.2 Protocol flags
        res += writer.writeUint8(message.getFlags().all, out);
        /// 3.1.2.10 Keep alive
        res += writer.writeUint16(message.getKeepAlive(), out);

        /// 3.1.3 Payload
        /// 3.1.3.1 DefaultConnection Id
        res += writer.writeString(message.getClientId(), out);

        if (message.getFlags().bits.willFlag) {
            /// 3.1.3.2 Will Topic
            res += writer.writeString(message.getWillTopic(), out);
            /// 3.1.3.3 Will Message
            res += writer.writeString(message.getWillMessage(), out);
        }

        if (message.getFlags().bits.username) {
            /// 3.1.3.4 User Name
            res += writer.writeString(message.getUserName(), out);
        }

        if (message.getFlags().bits.password) {
            /// 3.1.3.5 Password
            res += writer.writeString(message.getPassword(), out);
        }

        return res;
    }

    int Encoder::encodeConnAck(std::ostream &out, const message::ConnAckMessage &message) {
        Writer writer;

        size_t res = 0;
        /// 3.2.2 Variable header
        /// 3.2.2.1 Connect Acknowledge Flags
        res += writer.writeUint8(message.getFlags(), out);
        /// 3.2.2.2 Session Present
        /// 3.2.2.3 Connect Return code
        res += writer.writeUint8(message.getReasonCode(), out);

        return res;
    }

    int Encoder::encodePublish(std::ostream &out, const message::PublishMessage &message) {
        Writer writer;

        size_t res = 0;
        /// 3.3.2 Variable header
        /// 3.3.2.1 Topic Name
        res += writer.writeString(message.getTopic(), out);
        if (message.getHeader().bits.qos) {
            /// 3.3.2.2 Packet Identifier
            res += writer.writeUint16(message.getPacketIdentifier(), out);
        }

        /// 3.3.3 Payload
        res += writer.writeData(message.getMessage(), out);

        return res;
    }

    int Encoder::encodePubAck(std::ostream &out, const message::PubAckMessage &message) {
        Writer writer;

        size_t res = 0;
        /// 3.4.2 Variable header
        res += writer.writeUint16(message.getPacketIdentifier(), out);

        return res;
    }

    int Encoder::encodePubRec(std::ostream &out, const message::PubRecMessage &message) {
        Writer writer;

        size_t res = 0;
        /// 3.5.2 Variable header
        res += writer.writeUint16(message.getPacketIdentifier(), out);

        return res;
    }

    int Encoder::encodePubRel(std::ostream &out, const message::PubRelMessage &message) {
        Writer writer;

        size_t res = 0;
        /// 3.6.2 Variable header
        res += writer.writeUint16(message.getPacketIdentifier(), out);

        return res;
    }

    int Encoder::encodePubComp(std::ostream &out, const message::PubCompMessage &message) {
        Writer writer;

        size_t res = 0;
        /// 3.7.2 Variable header
        res += writer.writeUint16(message.getPacketIdentifier(), out);

        return res;
    }

    int Encoder::encodeSubscribe(std::ostream &out, const message::SubscribeMessage &message) {
        Writer writer;

        size_t res = 0;
        /// 3.8.2 Variable header
        /// 3.8.2.1 Variable header non normative example
        res += writer.writeUint16(message.getPacketIdentifier(), out);

        /// 3.8.3.1 Payload non normative example
        for (auto &topic : message.getTopics()) {
            res += writer.writeString(topic.getTopicFilter(), out);
            res += writer.writeUint8(topic.getQos(), out);
        }

        return res;
    }

    int Encoder::encodeSubAck(std::ostream &out, const message::SubAckMessage &message) {
        Writer writer;

        size_t res = 0;
        /// 3.9.2 Variable header
        res += writer.writeUint16(message.getPacketIdentifier(), out);
        /// 3.9.3 Payload
        res += writer.writeUint8(message.getReturnCode(), out);

        return res;
    }

    int Encoder::encodeUnSubscribe(std::ostream &out, const message::UnSubscribeMessage &message) {
        Writer writer;

        size_t res = 0;
        /// 3.10.2 Variable header
        res += writer.writeUint16(message.getPacketIdentifier(), out);
        /// 3.10.3.1 Payload non normative example
        for (auto &topicFilter : message.getTopicFilters()) {
            res += writer.writeString(topicFilter, out);
        }

        return res;
    }

    int Encoder::encodeUnSubAck(std::ostream &out, const message::UnSubAckMessage &message) {
        Writer writer;

        size_t res = 0;
        /// 3.11.2 Variable header
        res += writer.writeUint16(message.getPacketIdentifier(), out);

        return res;

    }

    int Encoder::encodePingReq(std::ostream &out, const message::PingReqMessage &message) {
        return 0;
    }

    int Encoder::encodePingResp(std::ostream &out, const message::PingRespMessage &message) {
        return 0;
    }

    int Encoder::encodeDisconnect(std::ostream &out, const message::DisconnectMessage &message) {
        return 0;
    }

}