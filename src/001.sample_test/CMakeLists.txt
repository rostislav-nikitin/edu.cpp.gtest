cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
message("GTEST_INCLUDE_DIRS = ${GTEST_INCLUDE_DIRS}")

add_library(lib lib.cpp)
add_executable(use_lib use_lib.cpp)
target_link_libraries(use_lib lib)

message("GTEST_LIBRARIES = ${GTEST_LIBRARIES}")

add_executable(test_runner test_runner.cpp)
target_link_libraries(test_runner lib gtest_main ${GTEST_LIBRARIES} pthread)
