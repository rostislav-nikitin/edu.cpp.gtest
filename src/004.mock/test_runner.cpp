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
	MOCK_METHOD(void, connect, ());
	MOCK_METHOD(void, disconnect, ());
	MOCK_METHOD(float, get_salary, (int), (const));
	MOCK_METHOD(void, update_salary, (int, float));
	MOCK_METHOD(std::vector<Employee>, get_salaries_range, (float), (const));
	MOCK_METHOD(std::vector<Employee>, get_salaries_range, (float, float),(const));
	//MOCK_METHOD(void, set_on_connect, (On_connect_callback));
	// Comma example
	//MOCK_METHOD((std::tuple<bool, int>), some_method, ());
	void member_function();
	void member_function_with_param(std::string param);
};

Database_connection_mock::Database_connection_mock(std::string connection_string) 
		: IDatabase_connection(connection_string)
{
}
void Database_connection_mock::member_function()
{
	std::cout << "member_function() called" << std::endl;
	throw std::runtime_error("Connection error.");
}

void Database_connection_mock::member_function_with_param(std::string param)
{
	std::cout << "membed_function_with_param(std::string param) [param='" << param << "' called" << std::endl;
	throw std::runtime_error("Connection error.");
}

//Times
TEST(EmployeeManagerTest, TestConnection)
{
	Database_connection_mock sut("localhost:1234");
	EXPECT_CALL(sut, connect());
	EXPECT_CALL(sut, disconnect());
	Employee_manager employee_manager(&sut);
}

TEST(EmployeeManagerTest, TestUpdateSalary)
{
	Database_connection_mock db_connection("localhost:1234");
	EXPECT_CALL(db_connection, connect());
	EXPECT_CALL(db_connection, disconnect());
	EXPECT_CALL(db_connection, update_salary(testing::_, 1200.5)).Times(1);

	Employee_manager sut(&db_connection);
	sut.set_salary(1, 1200.5);
}

TEST(EmployeeTestManager, TestGetSalary)
{
	int const employee_id = 50;
	int const another_employee_id = 90;

	float const expected_salary_amount = 6100.0;
	float const another_expected_salary_amount = 4500.0;

	Database_connection_mock db_connection("localhost:1234");
	EXPECT_CALL(db_connection, connect());
	EXPECT_CALL(db_connection, disconnect());
	EXPECT_CALL(db_connection, get_salary(employee_id))
			.WillOnce(testing::Return(expected_salary_amount));

	EXPECT_CALL(db_connection, get_salary(another_employee_id))
			.Times(1)
			.WillOnce(testing::Return(another_expected_salary_amount));

	Employee_manager sut(&db_connection);

	float actual_salary_amount = sut.get_salary(employee_id);
	ASSERT_EQ(expected_salary_amount, actual_salary_amount);

	float another_actual_salary_amount = sut.get_salary(another_employee_id);
	ASSERT_EQ(another_expected_salary_amount, another_actual_salary_amount);

}

//Behaviour
TEST(EmployeeTestManager, TestConnectionError)
{
	Database_connection_mock db_connection("localhost:1234");
	EXPECT_CALL(db_connection, connect()).WillOnce(testing::Throw(std::runtime_error("Connection error.")));

	ASSERT_THROW(Employee_manager employee_manager(&db_connection), std::runtime_error);
}

ACTION(ThrowException)
{
	std::cout << "ThrowException ACTION called" << std::endl;
	throw std::runtime_error("Connection error.");
}

TEST(EmployeeTestManager, TestConnectionErrorAction)
{
	Database_connection_mock db_connection("localhost:1234");
	EXPECT_CALL(db_connection, connect()).WillOnce(ThrowException());

	ASSERT_THROW(Employee_manager employee_manager(&db_connection), std::runtime_error);
}

void throw_exception()
{
	std::cout << "Free function 'throw_exception' called" << std::endl;
	throw std::runtime_error("Connection error.");
}

TEST(EmployeeTestManager, TestConnectionErrorFreeFunction)
{
	Database_connection_mock db_connection("localhost:1234");
	EXPECT_CALL(db_connection, connect()).WillOnce(throw_exception);

	ASSERT_THROW(Employee_manager employee_manager(&db_connection), std::runtime_error);
}

TEST(EmployeeTestManager, TestConnectionErrorLambda)
{
	Database_connection_mock db_connection("localhost:1234");
	EXPECT_CALL(db_connection, connect()).WillOnce(
					[]
					{
						std::cout << "Lambda called" << std::endl;
						throw std::runtime_error("Connection error.");
					}
	);

	ASSERT_THROW(Employee_manager employee_manager(&db_connection), std::runtime_error);
}

TEST(EmployeeTestManager, TestConnectionErrorMemberFunction)
{
	Database_connection_mock db_connection("localhost:1234");
	auto bound_method = std::bind(&Database_connection_mock::member_function, &db_connection);
	
	EXPECT_CALL(db_connection, connect()).WillOnce(::testing::InvokeWithoutArgs(bound_method));

	ASSERT_THROW(Employee_manager employee_manager(&db_connection), std::runtime_error);
}

TEST(EmployeeTestManager, TestConnectionErrorMemberFunctionWithParam)
{
	Database_connection_mock db_connection("localhost:1234");
	auto bound_method = std::bind(&Database_connection_mock::member_function_with_param, &db_connection, "Test Param");
	
	EXPECT_CALL(db_connection, connect()).WillOnce(::testing::InvokeWithoutArgs(bound_method));

	ASSERT_THROW(Employee_manager employee_manager(&db_connection), std::runtime_error);
}

//Matchers
TEST(EmployeeTestManager, TestMatchers)
{
	Database_connection_mock db_connection("localhost:1234");
	EXPECT_CALL(db_connection, connect()).Times(1);
	EXPECT_CALL(db_connection, disconnect()).Times(1);

	Employee_manager sut(&db_connection);
	const float salary_min = 4000.;
	const float salary_max = 10000.;

	std::vector<Employee> employees = std::vector({
					Employee(1, 6000., "John"),
					Employee(2, 7500.,"Mary"),
					Employee(3, 4300., "Derick")});

	EXPECT_CALL(db_connection, get_salaries_range(::testing::Ge(salary_min), ::testing::Le(salary_max)))
			.WillOnce(::testing::Return(employees));


	std::map<std::string, float> result = sut.get_salaries_between(salary_min, salary_max);

	for(std::map<std::string, float>::iterator it = result.begin(); it != result.end(); ++it)
	{
		std::cout << it->first << ": " << it->second << std::endl;
		EXPECT_THAT(it->second, testing::AllOf(testing::Gt(salary_min), testing::Lt(salary_max)));
	}
}

// Vector matchers
std::vector<int> generate_numbers(int n, int limit)
{
	std::vector<int> result;

	if(limit <= 0)
	{
		throw std::runtime_error("Limit shold be greated then zero.");
	}
	for(int i = 0; i < n; ++i)
	{
		result.push_back(i % limit);
	}

	return result;
}

TEST(VectorTest, TestElementsAre)
{
//Arrange
	std::vector<int> values = generate_numbers(5, 3);
//Assert
	ASSERT_THAT(values, ::testing::ElementsAre(0, 1, 2, 0, 1));
}

TEST(VectorTest, TestEach)
{
//Arrange
	std::vector<int> values = generate_numbers(5, 3);
//Assert
	ASSERT_THAT(values, ::testing::Each(::testing::AllOf(::testing::Ge(0), ::testing::Lt(3))));
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
