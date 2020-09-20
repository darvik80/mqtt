cmake_minimum_required(VERSION 3.17)
project(mqtt VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SRCS_G
        src/*.cpp
        src/message/*.cpp
        )

include_directories(
        /usr/local/include
        ${PROJECT_SOURCE_DIR}/src
)

find_package(Boost REQUIRED COMPONENTS system filesystem)

link_directories(
        /usr/local/lib
)

add_executable(mqtt ${SRCS_G})

add_subdirectory(testsuite)