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

    void Logger::init(const LoggerProperties &props) {
        log::register_simple_formatter_factory<log::trivial::severity_level, char>("Severity");

        if (props.file) {
            log::add_file_log(
                    log::keywords::file_name = props.fileName,
                    log::keywords::rotation_size = 10 * 1024 * 1024,
                    log::keywords::time_based_rotation = log::sinks::file::rotation_at_time_point(0, 0, 0),
                    log::keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%] %Message%",
                    log::keywords::auto_flush = true
            );
        }

        if (props.console) {
            log::add_console_log(
                    std::cout,
                    log::keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%] %Message%"
            );
        }

        log::core::get()->set_filter(
                log::trivial::severity >= props.level
        );

        log::add_common_attributes();
    }
}