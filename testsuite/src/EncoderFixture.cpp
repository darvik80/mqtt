//
// Created by Kishchenko, Ivan on 9/16/20.
//

#include "EncoderFixture.h"

using namespace mqtt;
using namespace mqtt::message;

BOOST_FIXTURE_TEST_SUITE(EncoderTest, EncoderFixture)

    BOOST_AUTO_TEST_CASE(encodeConnect) {
        uint8_t packet[] = {
                0x10, 0x25, 0x00, 0x06, 0x4d, 0x51, 0x49, 0x73,
                0x64, 0x70, 0x03, 0x02, 0x00, 0x05, 0x00, 0x17,
                0x70, 0x61, 0x68, 0x6f, 0x2f, 0x44, 0x44, 0x45,
                0x34, 0x44, 0x44, 0x41, 0x46, 0x34, 0x31, 0x30,
                0x38, 0x44, 0x33, 0x45, 0x33, 0x36, 0x33
        };

        boost::asio::streambuf buffer;

        auto msg = std::make_shared<ConnectMessage>();
        msg->setClientId("paho/DDE4DDAF4108D3E363");
        msg->setKeepAlive(5);

        encoder.encode(buffer, msg);

        size_t packetSize = sizeof(packet) / sizeof(packet[0]);
        for (size_t idx = 0; idx < packetSize; idx++, buffer.snextc()) {
            BOOST_CHECK(buffer.sgetc() == packet[idx]);
        }
    }

    BOOST_AUTO_TEST_CASE(encodeConnAck) {
        uint8_t packet[] = {
                0x20, 0x02, 0x00, 0x00
        };

        auto msg = std::make_shared<ConnAckMessage>();
        msg->setReasonCode(0);
        msg->setFlags(0);

        boost::asio::streambuf buffer;
        encoder.encode(buffer, msg);

        size_t packetSize = sizeof(packet) / sizeof(packet[0]);
        for (size_t idx = 0; idx < packetSize; idx++, buffer.snextc()) {
            BOOST_CHECK(buffer.sgetc() == packet[idx]);
        }
    }

    BOOST_AUTO_TEST_CASE(encodeSubscribe) {
        uint8_t packet[] = {
                0x82, 0x10, 0x00, 0x01, 0x00, 0x0b, 0x53, 0x61,
                0x6d, 0x70, 0x6c, 0x65, 0x54, 0x6f, 0x70, 0x69,
                0x63, 0x00
        };

        auto msg = std::make_shared<SubscribeMessage>();
        msg->setQos(1);
        msg->setPacketIdentifier(1);
        msg->addTopic("SampleTopic", 0);

        boost::asio::streambuf buffer;
        encoder.encode(buffer, msg);

        size_t packetSize = sizeof(packet) / sizeof(packet[0]);
        for (size_t idx = 0; idx < packetSize; idx++, buffer.snextc()) {
            BOOST_CHECK(buffer.sgetc() == packet[idx]);
        }
    }

    BOOST_AUTO_TEST_CASE(encodeSubAck) {
        uint8_t packet[] = {
                0x90, 0x03, 0x00, 0x01, 0x00
        };

        auto msg = std::make_shared<SubAckMessage>();
        msg->setPacketIdentifier(1);
        msg->setReturnCode(0);

        boost::asio::streambuf buffer;
        encoder.encode(buffer, msg);

        size_t packetSize = sizeof(packet) / sizeof(packet[0]);
        for (size_t idx = 0; idx < packetSize; idx++, buffer.snextc()) {
            BOOST_CHECK(buffer.sgetc() == packet[idx]);
        }
    }

    BOOST_AUTO_TEST_CASE(encodePublish) {
        uint8_t packet[] = {
                0x31, 0x30, 0x00, 0x0b, 0x53, 0x61, 0x6d, 0x70,
                0x6c, 0x65, 0x54, 0x6f, 0x70, 0x69, 0x63, 0x48,
                0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x66, 0x72, 0x6f,
                0x6d, 0x20, 0x74, 0x68, 0x65, 0x20, 0x50, 0x61,
                0x68, 0x6f, 0x20, 0x62, 0x6c, 0x6f, 0x63, 0x6b,
                0x69, 0x6e, 0x67, 0x20, 0x63, 0x6c, 0x69, 0x65,
                0x6e, 0x74
        };

        auto msg = std::make_shared<PublishMessage>();
        msg->setTopic("SampleTopic");

        msg->setMessage("Hello from the Paho blocking client");

        boost::asio::streambuf buffer;
        encoder.encode(buffer, msg);

        size_t packetSize = sizeof(packet) / sizeof(packet[0]);
        for (size_t idx = 0; idx < packetSize; idx++, buffer.snextc()) {
            BOOST_CHECK(buffer.sgetc() == packet[idx]);
        }
    }

    BOOST_AUTO_TEST_CASE(encodeDisconnect) {
        uint8_t packet[] = {
                0xe0, 00
        };

        auto msg = std::make_shared<DisconnectMessage>();
        boost::asio::streambuf buffer;
        encoder.encode(buffer, msg);

        size_t packetSize = sizeof(packet) / sizeof(packet[0]);
        for (size_t idx = 0; idx < packetSize; idx++, buffer.snextc()) {
            BOOST_CHECK(buffer.sgetc() == packet[idx]);
        }
    }

BOOST_AUTO_TEST_SUITE_END()