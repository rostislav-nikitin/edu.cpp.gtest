#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class Some_class
{
public:
	Some_class() = default;
	virtual void some_method();
};

void Some_class::some_method()
{
}

class Some_class_mock : public Some_class
{
public:
	Some_class_mock() = default;
	MOCK_METHOD0(some_method, void());
};

TEST(SomeClass, WhenSomeMethodCalledThenSuccess)
{
	Some_class_mock sut;
	EXPECT_CALL(sut, some_method()).Times(1);
	sut.some_method();
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
