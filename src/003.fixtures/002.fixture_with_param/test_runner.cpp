#include <iostream>
#include <gtest/gtest.h>

#include "validator.hpp"

class ValidatorFixture : public testing::TestWithParam<std::tuple<bool, int>>
{
protected:
	const int min = 25;
	const int max = 75;

	Validator sut{min, max};
};

TEST_P(ValidatorFixture, InRangeTests)
{
	std::tuple<bool, int> testData = GetParam();

	bool expected = std::get<0>(testData);
	int value = std::get<1>(testData);
	ASSERT_EQ(expected, sut.in_range(value));
}

INSTANTIATE_TEST_SUITE_P(InRangeTests, ValidatorFixture, testing::Values(
						std::make_tuple(false, -50),
						std::make_tuple(false, 0),
						std::make_tuple(false, 24),
						std::make_tuple(true, 25),
						std::make_tuple(true, 26),
						std::make_tuple(true, 50),
						std::make_tuple(true, 74),
						std::make_tuple(true, 75),
						std::make_tuple(false, 76),
						std::make_tuple(false, 100)));
						
int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
