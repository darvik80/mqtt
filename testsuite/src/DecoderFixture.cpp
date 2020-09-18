//
// Created by Kishchenko, Ivan on 9/16/20.
//

#include "DecoderFixture.h"

using namespace mqtt;
using namespace mqtt::message;

BOOST_FIXTURE_TEST_SUITE(DecoderTest, DecoderFixture)

    BOOST_AUTO_TEST_CASE(decodeConnect) {
        uint8_t packet[] = {
                0x10, 0x25, 0x00, 0x06, 0x4d, 0x51, 0x49, 0x73,
                0x64, 0x70, 0x03, 0x02, 0x00, 0x05, 0x00, 0x17,
                0x70, 0x61, 0x68, 0x6f, 0x2f, 0x44, 0x44, 0x45,
                0x34, 0x44, 0x44, 0x41, 0x46, 0x34, 0x31, 0x30,
                0x38, 0x44, 0x33, 0x45, 0x33, 0x36, 0x33
        };

        boost::asio::streambuf buffer;
        buffer.sputn((const char *) packet, sizeof(packet) / sizeof(packet[0]));

        decoder.decode(buffer, [](const mqtt::message::Message &msg) {
            auto &connMsg = dynamic_cast<ConnectMessage const &>(msg);
            BOOST_REQUIRE_EQUAL(3, connMsg.getProtocolLevel());
            BOOST_CHECK(std::string("MQIsdp").compare(connMsg.getProtocolName()));

            BOOST_CHECK(std::string("paho/34AAE54A75D839566E").compare(connMsg.getClientId()));
        });

    }

    BOOST_AUTO_TEST_CASE(decodeConnAck) {
        uint8_t packet[] = {
                0x20, 0x02, 0x00, 0x00
        };

        boost::asio::streambuf buffer;
        buffer.sputn((const char *) packet, sizeof(packet) / sizeof(packet[0]));

        decoder.decode(buffer, [](const mqtt::message::Message &msg) {
            auto &connAckMsg = dynamic_cast<ConnAckMessage const &>(msg);
            BOOST_REQUIRE_EQUAL(0, connAckMsg.getFlags());
            BOOST_REQUIRE_EQUAL(0, connAckMsg.getReasonCode());
        });
    }

    BOOST_AUTO_TEST_CASE(decodeSubscribe) {
        uint8_t packet[] = {
                0x82, 0x10, 0x00, 0x01, 0x00, 0x0b, 0x53, 0x61,
                0x6d, 0x70, 0x6c, 0x65, 0x54, 0x6f, 0x70, 0x69,
                0x63, 0x00
        };

        boost::asio::streambuf buffer;
        buffer.sputn((const char *) packet, sizeof(packet) / sizeof(packet[0]));

        decoder.decode(buffer, [](const mqtt::message::Message &msg) {
            auto &subsMsg = dynamic_cast<SubscribeMessage const &>(msg);
            BOOST_REQUIRE_EQUAL(1, subsMsg.getPacketIdentifier());
            BOOST_REQUIRE_EQUAL(1, subsMsg.getTopics().size());
            BOOST_CHECK(std::string("SampleTopic").compare(subsMsg.getTopics()[0].getTopicFilter()));
            BOOST_REQUIRE_EQUAL(0, subsMsg.getTopics()[0].getQos());
            BOOST_REQUIRE_EQUAL(1, subsMsg.getTopics().size());
        });
    }

    BOOST_AUTO_TEST_CASE(decodeSubAck) {
        uint8_t packet[] = {
                0x90, 0x03, 0x00, 0x01, 0x00
        };

        boost::asio::streambuf buffer;
        buffer.sputn((const char *) packet, sizeof(packet) / sizeof(packet[0]));

        decoder.decode(buffer, [](const mqtt::message::Message &msg) {
            auto &subAckMsg = dynamic_cast<SubAckMessage const &>(msg);
            BOOST_REQUIRE_EQUAL(1, subAckMsg.getPacketIdentifier());
            BOOST_REQUIRE_EQUAL(0, subAckMsg.getReturnCode());
        });
    }

    BOOST_AUTO_TEST_CASE(decodePublish) {
        uint8_t packet[] = {
                0x31, 0x30, 0x00, 0x0b, 0x53, 0x61, 0x6d, 0x70,
                0x6c, 0x65, 0x54, 0x6f, 0x70, 0x69, 0x63, 0x48,
                0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x66, 0x72, 0x6f,
                0x6d, 0x20, 0x74, 0x68, 0x65, 0x20, 0x50, 0x61,
                0x68, 0x6f, 0x20, 0x62, 0x6c, 0x6f, 0x63, 0x6b,
                0x69, 0x6e, 0x67, 0x20, 0x63, 0x6c, 0x69, 0x65,
                0x6e, 0x74
        };

        boost::asio::streambuf buffer;
        buffer.sputn((const char *) packet, sizeof(packet) / sizeof(packet[0]));

        decoder.decode(buffer, [](const mqtt::message::Message &msg) {
            auto &pubMsg = dynamic_cast<PublishMessage const &>(msg);
            BOOST_REQUIRE_EQUAL(0, pubMsg.getHeader().bits.qos);
            BOOST_REQUIRE_EQUAL(0, pubMsg.getPacketIdentifier());
            BOOST_CHECK(std::string("SampleTopic").compare(pubMsg.getTopic()));
        });
    }

BOOST_AUTO_TEST_SUITE_END()