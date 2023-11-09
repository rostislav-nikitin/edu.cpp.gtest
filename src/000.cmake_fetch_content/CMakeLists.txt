cmake_minimum_required(VERSION 3.14)

project(googletest_fetchcontent_sample)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)

FetchContent_Declare(googletest
		GIT_REPOSITORY https://github.com/google/googletest
		GIT_TAG v1.14.0)

FetchContent_GetProperties(googletest)

if(NOT googletest_POPULATED)
	FetchContent_Populate(googletest)
	add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BUILD_DIR})
endif()

add_executable(test_runner test_runner.cpp)
target_link_libraries(test_runner gtest_main gmock_main)
