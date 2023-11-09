#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include <string>

class Employee
{
private:
	int _id;
	float _salary;
	std::string _name;

public:
	Employee() = default;
	Employee(int id, float salary, std::string name);
	int get_id() const;
	float get_salary() const;
	std::string get_name() const;
};

#endif
