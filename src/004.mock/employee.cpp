#include <string>

#include "employee.hpp"

Employee::Employee(int id, float salary, std::string name)
		: _id(id), _salary(salary), _name(name)
{
}

int Employee::get_id() const
{
	return _id;
}

float Employee::get_salary() const
{
	return _salary;
}

std::string Employee::get_name() const
{
	return _name;
}
