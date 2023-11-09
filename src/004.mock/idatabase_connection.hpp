#ifndef IDATABASE_CONNECTION_HPP
#define IDATABASE_CONNECTION_HPP

#include <vector>
#include <functional>

#include "employee.hpp"

class IDatabase_connection
{
public:
	class Static_call_helper
	{
	public:
		virtual void call_static_increase_connections_count();
	};
	//typedef void(* On_connect_callback)();
private:

	virtual void on_connect();

	static unsigned int connections_count;
	static void increase_connections_count();

protected:
	std::string _connection_string;	
	Static_call_helper *_static_call_helper;
	//On_connect_callback _on_connect_callback;
	std::function<void(int, std::string)> _on_connect_callback;

public:
	IDatabase_connection(std::string connection_string, Static_call_helper *static_call_helper = nullptr);

	virtual void connect();
	virtual void disconnect();

	virtual float get_salary(int id) const = 0;
	virtual void update_salary(int id, float new_salary) = 0;

	virtual std::vector<Employee> get_salaries_range(float min) const = 0;
	virtual std::vector<Employee> get_salaries_range(float min, float max) const = 0;

	//virtual void set_on_connect(On_connect_callback);
	virtual void set_on_connect(std::function<void(int, std::string)> callback);

	friend class Static_call_helper;
};

#endif
