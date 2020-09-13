//
// Created by Ivan Kishchenko on 12.09.2020.
//

#include "Encoder.h"
#include "Writer.h"

namespace mqtt {
    void Encoder::encode(boost::asio::streambuf &buf, function::Supplier<message::Message::MessagePtr> &consumer) {
        boost::asio::streambuf data;
        std::ostream body(&data);

        auto msg = consumer.get();

        int dataSize = 0;
        switch (msg->getType()) {
            case MQTT_MSG_CONNECT:
                encodeConnect(body, *(dynamic_cast<message::ConnectMessage*>(msg.get())));
                break;
            case MQTT_MSG_CONNACK:
                encodeConnAck(body, *(dynamic_cast<message::ConnAckMessage*>(msg.get())));
                break;
            case MQTT_MSG_PUBLISH:
                encodePublish(body, *(dynamic_cast<message::PublishMessage*>(msg.get())));
                break;
            case MQTT_MSG_PUBACK:
                encodePubAck(body, *(dynamic_cast<message::PubAckMessage*>(msg.get())));
                break;
            case MQTT_MSG_PUBREC:
                encodePubRec(body, *(dynamic_cast<message::PubRecMessage*>(msg.get())));
                break;
            case MQTT_MSG_PUBREL:
                encodePubRel(body, *(dynamic_cast<message::PubRelMessage*>(msg.get())));
                break;
            case MQTT_MSG_PUBCOMP:
                encodePubComp(body, *(dynamic_cast<message::PubCompMessage*>(msg.get())));
                break;
            case MQTT_MSG_SUBSCRIBE:
                encodeSubscribe(body, *(dynamic_cast<message::SubscribeMessage*>(msg.get())));
                break;
            default:
                break;

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

        /// 3.1.2 Variable header
        /// 3.1.2.1 Protocol name
        res += writer.writeString("MQIsdp", out);
        /// 3.1.2.2 Protocol version
        res += writer.writeUint8((uint8_t) 3, out);
        /// 3.1.2.2 Protocol flags
        res += writer.writeUint8(message.getFlags().all, out);
        // ...
        /// 3.1.2.10 Keep alive
        res += writer.writeUint16((uint16_t) 10, out);

        /// 3.1.3 Payload
        /// 3.1.3.1 Client Id
        res += writer.writeString(message.getClientId(), out);

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
        writer.writeString(message.getTopic(), out);
        /// 3.3.2.2 Packet Identifier
        writer.writeUint16(message.getPacketIdentifier(), out);

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

}