#include <string>
#include <iostream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "employee.hpp"
#include "idatabase_connection.hpp"
#include "employee_manager.hpp"

class Database_connection_mock : public IDatabase_connection
{
public:
	Database_connection_mock(std::string connection_string);

	MOCK_METHOD(float, get_salary, (int), (const));
	MOCK_METHOD(void, update_salary, (int, float));
	MOCK_METHOD(std::vector<Employee>, get_salaries_range, (float), (const));
	MOCK_METHOD(std::vector<Employee>, get_salaries_range, (float, float),(const));
	//MOCK_METHOD(void, set_on_connect, (On_connect_callback));

};

Database_connection_mock::Database_connection_mock(std::string connection_string) 
		: IDatabase_connection(connection_string)
{
}



//Callbacks
void on_connect_callback()
{
	std::cout << "On connect callback called" << std::endl;
}
/*
TEST(CallbackTest, WhenCallbackThenSuccess)
{
	Database_connection_mock sut("localhost:1234");

	sut.set_on_connect(on_connect_callback);
	sut.connect();
}
*/

TEST(CallbackTest, WhenCallbackThenSuccess)
{
	Database_connection_mock sut("localhost:1234");
	::testing::MockFunction<void(int, std::string)> on_connect_callback_mock;

	sut.set_on_connect(on_connect_callback_mock.AsStdFunction());
	EXPECT_CALL(on_connect_callback_mock, Call(1, ::testing::_));
	sut.connect();
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
