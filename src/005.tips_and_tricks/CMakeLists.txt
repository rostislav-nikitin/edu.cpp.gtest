cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD, 14)

find_package(GTest)

add_executable(test_runner test_runner.cpp)
target_link_libraries(test_runner gtest)
