cmake_minimum_required(VERSION 3.17)
project(mqtt_testsuite VERSION 1.0)

file(GLOB TEST_SRCS
        src/*.cpp
        ../src/Encoder.h
)

include_directories(
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/../src
)

enable_testing()

find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

add_executable(mqtt_testsuite ${TEST_SRCS})

target_link_libraries(mqtt_testsuite PUBLIC
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        )

add_test(NAME mqtt_testsuite WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} COMMAND mqtt_testsuite)