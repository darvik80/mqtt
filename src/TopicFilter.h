//
// Created by Ivan Kishchenko on 30.12.2020.
//

#ifndef MQTT_TOPICFILTER_H
#define MQTT_TOPICFILTER_H

#include <boost/tokenizer.hpp>

#include <string>
#include <vector>

namespace mqtt {

#define TOPIC_SEPARATOR         '/'
#define TOPIC_SINGLE_WILDCARD   '+'
#define TOPIC_MULTI_WILDCARD    '#'

    class TopicFilter {
    private:
        std::string _filter;
    public:
        TopicFilter(std::string_view topicFilter);

        bool filter(std::string_view topic);

        [[nodiscard]] const std::string &getFilter() const;
    };

}


#endif //MQTT_TOPICFILTER_H
