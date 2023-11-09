#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "account.hpp"

class AccountTestFixture : public testing::Test
{
public:
	void SetUp() override;
	void TearDown() override;
protected:
	const double deposite_amount = 10.5;
	const double less_withdraw_amount = deposite_amount / 2.;
	const double greater_withdraw_amount = deposite_amount * 2.;

	Account sut;
};

void AccountTestFixture::SetUp()
{
	sut.deposite(deposite_amount);
}

void AccountTestFixture::TearDown()
{
}

TEST_F(AccountTestFixture, WhenNewAccountThenBalanceIsZero)
{
//Arange
	Account local_sut;
//Act
//Assert
	ASSERT_EQ(0, local_sut.get_balance());
}

TEST_F(AccountTestFixture, WhenDepositThenBalanceIsAmountOfDeposite)
{
//Arange
//	Account sut;
//Act
//	sut.deposite(deposite_amount);
//Assert
	ASSERT_EQ(deposite_amount, sut.get_balance());
}

TEST_F(AccountTestFixture, WhenWithdawLessThenBalanceThenBalanceMinusAmountOfWithdraw)
{
//Arange
//	Account sut;
//Act
//	sut.deposite(deposite_amount);
	sut.withdraw(less_withdraw_amount);
//Assert
	ASSERT_EQ(deposite_amount - less_withdraw_amount, sut.get_balance());
}

TEST_F(AccountTestFixture, WhenWithdrawAmountGraterThenBalanceThenThrow)
{
//Arange
//	Account sut;
//Act
//	sut.deposite(deposite_amount);
//Assert
	ASSERT_ANY_THROW(sut.withdraw(greater_withdraw_amount));
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
