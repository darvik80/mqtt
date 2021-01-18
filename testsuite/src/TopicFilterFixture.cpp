//
// Created by Ivan Kishchenko on 30.12.2020.
//

#include "TopicFilterFixture.h"

BOOST_FIXTURE_TEST_SUITE(TopicFilterTest, TopicFilterFixture)

    BOOST_AUTO_TEST_CASE(filter) {
        mqtt::TopicFilter filter{"hello/world"};
        BOOST_REQUIRE_EQUAL(true, filter.filter("hello/world"));
        BOOST_REQUIRE_EQUAL(false, filter.filter("hello/test"));
        BOOST_REQUIRE_EQUAL(false, filter.filter("hello/world/test"));

        filter = mqtt::TopicFilter{"+/world"};
        BOOST_REQUIRE_EQUAL(true, filter.filter("hello/world"));
        BOOST_REQUIRE_EQUAL(false, filter.filter("hello/test"));

        filter = mqtt::TopicFilter{"+/world/+/temperature"};
        BOOST_REQUIRE_EQUAL(true, filter.filter("hello/world/test/temperature"));
        BOOST_REQUIRE_EQUAL(false, filter.filter("hello/test/test/temperature"));
        BOOST_REQUIRE_EQUAL(false, filter.filter("hello/world/test/status"));

        filter = mqtt::TopicFilter{"+/world/+"};
        BOOST_REQUIRE_EQUAL(true, filter.filter("hello/world/test"));
        BOOST_REQUIRE_EQUAL(false, filter.filter("hello/test/test"));

        filter = mqtt::TopicFilter{"hello/world/#"};
        BOOST_REQUIRE_EQUAL(true, filter.filter("hello/world/test"));
        BOOST_REQUIRE_EQUAL(true, filter.filter("hello/world"));

        filter = mqtt::TopicFilter{"hello/+/#"};
        BOOST_REQUIRE_EQUAL(true, filter.filter("hello/world/test"));
        BOOST_REQUIRE_EQUAL(true, filter.filter("hello/world"));
        BOOST_REQUIRE_EQUAL(false, filter.filter("test/world/test"));
    }

    BOOST_AUTO_TEST_CASE(getFilter) {
        mqtt::TopicFilter filter{"hello/world"};
        BOOST_REQUIRE_EQUAL(std::string("hello/world"), filter.getFilter());
    }

BOOST_AUTO_TEST_SUITE_END()