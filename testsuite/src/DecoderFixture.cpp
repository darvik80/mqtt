//
// Created by Ivan Kishchenko on 05.09.2020.
//

#include "DecoderFixture.h"

#include <boost/asio.hpp>

BOOST_FIXTURE_TEST_SUITE(DecoderTest, DecoderFixture)

    BOOST_AUTO_TEST_CASE(readUint8) {
        boost::asio::streambuf buf;
        buf.sputc(0x15);
        std::istream inc(&buf);

        uint8_t val = _decoder.readUint8(inc);

        BOOST_REQUIRE_EQUAL(0x15, val);
        BOOST_REQUIRE_EQUAL(0, buf.size());
    }

    BOOST_AUTO_TEST_CASE(readUint16) {
        boost::asio::streambuf buf;
        buf.sputc(0x15);
        buf.sputc(0x51);
        std::istream inc(&buf);

        uint16_t val = _decoder.readUint16(inc);

        BOOST_REQUIRE_EQUAL(0x1551, val);
        BOOST_REQUIRE_EQUAL(0, buf.size());
    }

    BOOST_AUTO_TEST_CASE(readUint32) {
        boost::asio::streambuf buf;
        buf.sputc(0x15);
        buf.sputc(0x51);
        buf.sputc(0x7f);
        buf.sputc(0xf7);
        std::istream inc(&buf);

        uint32_t val = _decoder.readUint32(inc);

        BOOST_REQUIRE_EQUAL(0x15517ff7, val);
        BOOST_REQUIRE_EQUAL(0, buf.size());
    }

    BOOST_AUTO_TEST_CASE(readVariableInt) {
        boost::asio::streambuf buf;
        buf.sputc(0xd6);
        buf.sputc(0xe8);
        buf.sputc(0x48);
        std::istream inc(&buf);

        int val = _decoder.readVariableInt(inc);

        BOOST_REQUIRE_EQUAL(0x123456, val);
        BOOST_REQUIRE_EQUAL(0, buf.size());
    }

    BOOST_AUTO_TEST_CASE(writeString) {
        boost::asio::streambuf buf;
        buf.sputc(0x00);
        buf.sputc(0x05);
        buf.sputn("Hello", 0x05);

        std::istream inc(&buf);

        std::string str = _decoder.readString(inc);

        BOOST_REQUIRE_EQUAL("Hello", str.c_str());
        BOOST_REQUIRE_EQUAL(0, buf.size());
    }

BOOST_AUTO_TEST_SUITE_END()