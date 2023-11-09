cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

#add_library(employee employee.cpp)

#add_library(idatabase_connection idatabase_connection.cpp)
#target_link_libraries(idatabase_connection employee)

#add_library(employee_manager employee_manager.cpp)
#target_link_libraries(employee_manager employee idatabase_connection)

#set(APP_LIBRARIES employee idatabase_connection employee_manager)

add_executable(test_runner employee.cpp idatabase_connection.cpp employee_manager.cpp test_runner.cpp)
target_link_libraries(test_runner ${APP_LIBRARIES} gmock gtest pthread)

add_executable(test_callback_runner employee.cpp idatabase_connection.cpp employee_manager.cpp test_callback_runner.cpp)
target_link_libraries(test_callback_runner ${APP_LIBRARIES} gmock gtest pthread)

add_executable(test_private_and_static_runner employee.cpp idatabase_connection.cpp employee_manager.cpp test_private_and_static_runner.cpp)
target_link_libraries(test_private_and_static_runner ${APP_LIBRARIES} gmock gtest pthread)
