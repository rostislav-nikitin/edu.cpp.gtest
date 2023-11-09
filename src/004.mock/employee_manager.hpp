#ifndef EMPLOYEE_MANAGER_HPP
#define EMPLOYEE_MANAGER_HPP

#include <string>
#include <vector>
#include <map>

#include "employee.hpp"
#include "idatabase_connection.hpp"

class Employee_manager
{
private:
	IDatabase_connection *_db_connection;

	std::map<std::string, float> vector_to_map(std::vector<Employee> const &employees) const;
public:
	Employee_manager(IDatabase_connection *db_connection);
	~Employee_manager();

	float get_salary(int employee_id) const;
	void set_salary(int employee_id, float new_salary);

	std::map<std::string, float> get_salaries_greater(float min) const;	
	std::map<std::string, float> get_salaries_between(float min, float max) const;	
	
};

#endif
