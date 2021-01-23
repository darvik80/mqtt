cmake_minimum_required(VERSION 3.17)
project(mqtt VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SRCS_G
        src/*.cpp
        src/message/*.cpp
        src/logging/*.cpp
        src/event/*.cpp
        src/command/*.cpp
        )

include_directories(
        /usr/local/include
        ${PROJECT_SOURCE_DIR}/src
)

add_definitions(-DBOOST_LOG_DYN_LINK)

find_package(Boost REQUIRED COMPONENTS system program_options filesystem thread log log_setup)
find_package(Threads)

link_directories(
        /usr/local/lib
)

add_library(mqtt STATIC ${SRCS_G})

target_link_libraries(mqtt ${Boost_LIBRARIES})

add_subdirectory(testsuite)