cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

add_library(lib lib.cpp)
add_executable(test_runner test_runner.cpp)

target_link_libraries(test_runner lib gtest_main ${GTEST_LIBRARIES} pthread)
