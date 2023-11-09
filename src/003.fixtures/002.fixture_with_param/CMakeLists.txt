cmake_minimum_required(VERSION 3.14)

find_package(GTest REQUIRED)

add_library(validator validator.cpp)

add_executable(test_runner test_runner.cpp)

target_link_libraries(test_runner validator ${GTEST_LIBRARIES} pthread)
