#include <string>
#include <iostream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "employee.hpp"
#include "idatabase_connection.hpp"
#include "employee_manager.hpp"

class Static_call_helper_mock : public IDatabase_connection::Static_call_helper
{
public:
	MOCK_METHOD(void, call_static_increase_connections_count, (), ());
};

class Database_connection_mock : public IDatabase_connection
{
public:
	Database_connection_mock(std::string connection_string, IDatabase_connection::Static_call_helper *static_call_helper = nullptr);

	MOCK_METHOD(float, get_salary, (int), (const));
	MOCK_METHOD(void, update_salary, (int, float));
	MOCK_METHOD(std::vector<Employee>, get_salaries_range, (float), (const));
	MOCK_METHOD(std::vector<Employee>, get_salaries_range, (float, float),(const));
	MOCK_METHOD(void, on_connect, (), (override));
	MOCK_METHOD(void, some_method_not_exists_in_patent, ());
};

Database_connection_mock::Database_connection_mock(
				std::string connection_string, 
				IDatabase_connection::Static_call_helper *static_call_helper) : 
		IDatabase_connection(connection_string, static_call_helper)
{
}
/*
Database_connection_mock::Database_connection_mock(std::string connection_string) 
		: IDatabase_connection(connection_string)
{
}
*/

TEST(PrivateMethodTest, OnConnectTest)
{
	Database_connection_mock sut("localhost:1234");
	EXPECT_CALL(sut, on_connect());
	sut.connect();
}

TEST(PrivateStaticMethodTest, IncreaseConnectinsCountTest)
{
	Static_call_helper_mock call_helper_mock;
	EXPECT_CALL(call_helper_mock, call_static_increase_connections_count());
	Database_connection_mock sut("localhost:1234", &call_helper_mock);
//	sut.connect();
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
