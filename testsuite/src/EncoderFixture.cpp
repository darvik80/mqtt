//
// Created by Ivan Kishchenko on 05.09.2020.
//

#include "EncoderFixture.h"

#include <boost/asio.hpp>

BOOST_FIXTURE_TEST_SUITE(EncoderTest, EncoderFixture)

    BOOST_AUTO_TEST_CASE(writeUint8) {
        boost::asio::streambuf buf;
        std::ostream out(&buf);

        uint8_t val = 0x15;
        _encoder.writeUint8(val, out);

        BOOST_REQUIRE_EQUAL(1, buf.size());
        BOOST_REQUIRE_EQUAL(val, buf.sgetc());
    }

    BOOST_AUTO_TEST_CASE(writeUint16) {
        boost::asio::streambuf buf;
        std::ostream out(&buf);

        uint16_t val = 0x1551;
        _encoder.writeUint16(val, out);

        BOOST_REQUIRE_EQUAL(2, buf.size());
        BOOST_REQUIRE_EQUAL(0x15, buf.sgetc());
        buf.snextc();
        BOOST_REQUIRE_EQUAL(0x51, buf.sgetc());
    }

    BOOST_AUTO_TEST_CASE(writeUint32) {
        boost::asio::streambuf buf;
        std::ostream out(&buf);

        uint32_t val = 0x15517ff7;
        _encoder.writeUint32(val, out);

        BOOST_REQUIRE_EQUAL(4, buf.size());
        BOOST_REQUIRE_EQUAL(0x15, buf.sgetc());
        buf.snextc();
        BOOST_REQUIRE_EQUAL(0x51, buf.sgetc());
        buf.snextc();
        BOOST_REQUIRE_EQUAL(0x7f, buf.sgetc());
        buf.snextc();
        BOOST_REQUIRE_EQUAL(0xf7, buf.sgetc());
    }

    BOOST_AUTO_TEST_CASE(writeVariableInt) {
        boost::asio::streambuf buf;
        std::ostream out(&buf);

        int val = 0x00123456;
        _encoder.writeVariableInt(val, out);

        BOOST_REQUIRE_EQUAL(3, buf.size());
        BOOST_REQUIRE_EQUAL(0xd6, buf.sgetc());
        buf.snextc();
        BOOST_REQUIRE_EQUAL(0xe8, buf.sgetc());
        buf.snextc();
        BOOST_REQUIRE_EQUAL(0x48, buf.sgetc());
    }

    BOOST_AUTO_TEST_CASE(writeString) {
        boost::asio::streambuf buf;
        std::ostream out(&buf);

        std::string str = "Hello";
        _encoder.writeString(str, out);

        BOOST_REQUIRE_EQUAL(2 + str.size(), buf.size());
        BOOST_REQUIRE_EQUAL(0x00, buf.sgetc());
        buf.snextc();
        BOOST_REQUIRE_EQUAL(0x05, buf.sgetc());
        buf.snextc();
        BOOST_REQUIRE_EQUAL('H', buf.sgetc());
        buf.snextc();
        BOOST_REQUIRE_EQUAL('e', buf.sgetc());
        buf.snextc();
        BOOST_REQUIRE_EQUAL('l', buf.sgetc());
        buf.snextc();
        BOOST_REQUIRE_EQUAL('l', buf.sgetc());
        buf.snextc();
        BOOST_REQUIRE_EQUAL('o', buf.sgetc());
    }

BOOST_AUTO_TEST_SUITE_END()