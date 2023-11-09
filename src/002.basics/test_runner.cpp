#include <vector>
#include <gtest/gtest.h>

#include "lib.h"


//count_positive
TEST(CountPositive, WhenPositivesExistsThenCount)
{
	//Arrange
	std::vector<int> data = std::vector<int>({1, 3, -5, 6, -7, 55, -6});
	//Act
	int result = Lib::count_positives(data);
	//Assert
	ASSERT_EQ(4, result);
}

TEST(CountPositive, WhenEmptyThenZero)
{
	//Arrange
	std::vector<int> data;
	//Act
	int result = Lib::count_positives(data);
	//Assert
	ASSERT_EQ(0, result);
}

TEST(CountPositive, WhenOnlyNegativesThenZero)
{
	//Arrange
	std::vector<int> data = std::vector<int>({-1, -3, -5, -6, -7, -55, -6});
	//Act
	int result = Lib::count_positives(data);
	//Assert
	ASSERT_EQ(0, result);
}

//to_upper_case
TEST(ToUpperCase, WhenStringEqualsThenSuccess)
{
	//Arrange
	char in_str[] = "Hello World";
	//Act
	Lib::to_upper_case(in_str);
	//Assert
	ASSERT_STREQ("HELLO WORLD", in_str);
}

TEST(ToUpperCase, WhenStringIgnoerCaseEqualsThenSuccess)
{
	//Arrange
	char in_str[] = "Hello World";
	//Act
	Lib::to_upper_case(in_str);
	//Assert
	ASSERT_STRCASEEQ("hello world", in_str);
}

TEST(ToUpperCase, WhenStringAsStdStringEqualsThenSuccess)
{
	//Arrange
	char in_str[] = "Hello World";
	//Act
	Lib::to_upper_case(in_str);
	//Assert
	ASSERT_EQ("HELLO WORLD", std::string(in_str));
}

//sqrt
TEST(Sqrt, WhenNegativeThenAnyException)
{
//Arrange
	int x = -10;
//Act/Assert
	ASSERT_ANY_THROW(Lib::sqrt(x));
}

TEST(Sqrt, WhenNegativeThenTypedException)
{
//Arrange
	int x = -10;
//Act/Assert
//	ASSERT_THROW(Lib::sqrt(x), char const *);
	ASSERT_THROW(Lib::sqrt(x), std::runtime_error);
}

TEST(Sqrt, WhenPositiveThenSuccess)
{
//Arrange
	int x = 10;
//Act/Assert
	ASSERT_NO_THROW(Lib::sqrt(x));
}
