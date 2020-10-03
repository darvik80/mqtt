//
// Created by Kishchenko, Ivan on 10/2/20.
//

#include "Logger.h"

#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>

#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

using namespace boost;

namespace mqtt::logging {


    void Logger::init() {
        log::register_simple_formatter_factory<log::trivial::severity_level, char>("Severity");

        log::add_file_log(
                log::keywords::file_name = "mqtt.log",
                log::keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%] [%LineID%] %Message%"
        );


        log::add_console_log(
                std::cout,
                log::keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%] %Message%"
        );


        log::core::get()->set_filter(
                log::trivial::severity >= log::trivial::info
        );

        log::add_common_attributes();
    }
}