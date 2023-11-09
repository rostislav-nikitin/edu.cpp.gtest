#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account
{
	private:
		double _balance;
	public:
		Account();
		void deposite(double amount);
		void withdraw(double amount);
		double get_balance() const;
		void transfer(double amount, Account &to);
};

#endif
