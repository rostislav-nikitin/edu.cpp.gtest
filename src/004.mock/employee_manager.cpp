#include <string>
#include <vector>
#include <map>

#include "employee_manager.hpp"

std::map<std::string, float> Employee_manager::vector_to_map(std::vector<Employee> const &employees) const
{
	std::map<std::string, float> result;

	for(Employee const &employee : employees)
		result[employee.get_name()] = employee.get_salary();

	return result;
}

Employee_manager::Employee_manager(IDatabase_connection *db_connection) : _db_connection(db_connection)
{
	_db_connection->connect();
}

Employee_manager::~Employee_manager()
{
	_db_connection->disconnect();
}


float Employee_manager::get_salary(int employee_id) const
{
	return _db_connection->get_salary(employee_id);
}

void Employee_manager::set_salary(int employee_id, float new_salary)
{
	_db_connection->update_salary(employee_id, new_salary);
}

std::map<std::string, float> Employee_manager::get_salaries_greater(float min) const
{
	return vector_to_map(_db_connection->get_salaries_range(min));
}

std::map<std::string, float> Employee_manager::get_salaries_between(float min, float max) const
{
	return vector_to_map(_db_connection->get_salaries_range(min, max));
}
