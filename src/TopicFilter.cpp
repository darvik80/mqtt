//
// Created by Ivan Kishchenko on 30.12.2020.
//

#include "TopicFilter.h"
#include <boost/algorithm/string.hpp>

namespace mqtt {

    TopicFilter::TopicFilter(std::string_view topicFilter)
    : _filter(topicFilter)
    {

    }

    bool TopicFilter::filter(std::string_view topic) {
        auto f = _filter.begin();
        auto t = topic.begin();
        while (f != _filter.end() && t != topic.end()) {
            if (*f == TOPIC_SINGLE_WILDCARD) {
                // process '+'
                while (t != topic.end() && *t != TOPIC_SEPARATOR) t++;
                f++;
                continue;
            }

            if (*f == TOPIC_MULTI_WILDCARD) {
                return true;
            }

            if (*f != *t) {
                return false;
            }

            f++, t++;
        }

        if (t == topic.end() && f == _filter.end()) {
            return true;
        }

        if (t == topic.end() && f != _filter.end() && *f == TOPIC_SEPARATOR) {
            f++;
            if (f != _filter.end() && *f == TOPIC_MULTI_WILDCARD) {
                return true;
            }
        }

        return false;
    }

    const std::string &TopicFilter::getFilter() const {
        return _filter;
    }
}