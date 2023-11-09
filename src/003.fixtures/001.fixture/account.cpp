#include <stdexcept>

#include "account.hpp"

Account::Account() : _balance(0) 
{
}

void Account::deposite(double amount)
{
	_balance += amount;
}

void Account::withdraw(double amount)
{
	if(amount > _balance)
		throw std::runtime_error("Insufficient amount.");

	_balance -= amount;
}

double Account::get_balance() const
{
	return _balance;
}

void Account::transfer(double amount, Account &to)
{
	withdraw(amount);
	to.deposite(amount);
}
