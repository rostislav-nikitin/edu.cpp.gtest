#include <string>
#include <iostream>

#include "idatabase_connection.hpp"

unsigned int IDatabase_connection::connections_count = 0;

void IDatabase_connection::Static_call_helper::call_static_increase_connections_count()
{
	IDatabase_connection::increase_connections_count();
}

void IDatabase_connection::increase_connections_count()
{
	IDatabase_connection::connections_count++;
	std::cout << "conections_count: " << connections_count << std::endl;
}

IDatabase_connection::IDatabase_connection(std::string connection_string, Static_call_helper *static_call_helper)
		: _connection_string(connection_string), _static_call_helper(static_call_helper)
{
	if(_static_call_helper != nullptr)
	{
		std::cout << "_static_call_helper is NOT nullptr";
		_static_call_helper->call_static_increase_connections_count();
	}
	else
	{
		std::cout << "_static_call_helper IS nullptr";
		IDatabase_connection::increase_connections_count();
	}
}

void IDatabase_connection::on_connect()
{
	std::cout << "on_connect() called" << std::endl;
}

void IDatabase_connection::connect()
{
	if(_on_connect_callback != nullptr)
	{
		_on_connect_callback(1, "Connected");
	}
	on_connect();
	std::cout << "Connected to db" << std::endl;
}

void IDatabase_connection::disconnect()
{
	std::cout << "Disconnected from db" << std::endl;
}
/*
void IDatabase_connection::set_on_connect(On_connect_callback callback)
{
	_on_connect_callback = callback;
}
*/

void IDatabase_connection::set_on_connect(std::function<void(int, std::string)> callback)
{
	_on_connect_callback = callback;
}
