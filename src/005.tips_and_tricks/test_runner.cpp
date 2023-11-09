#include <gtest/gtest.h>

TEST(UnixSuite, DummyTest1)
{
	#ifdef __WIN32
	FAIL()
	#else
	SUCCEED();
	#endif
}

TEST(UnixSuite, DummyTest2)
{
	#ifdef __WIN32
	FAIL()
	#else
	SUCCEED();
	#endif
}

TEST(Win32Suite, DummyTest1)
{
	#ifdef __WIN32
	SUCCEDD()
	#else
	FAIL();
	#endif
}
TEST(Win32Suite, DummyTest2)
{
	#ifdef __WIN32
	SUCCEED()
	#else
	FAIL();
	#endif
}
TEST(Win32Suite, DummyTest3)
{
	#ifdef __WIN32
	SUCCEED()
	#else
	FAIL();
	#endif
}
int main(int argc, char **argv)
{
	/*
	#ifdef __WIN32
	// Run only filtered out tests
	::testing::GTEST_FLAG(filter) = "Win32Suite.*";
	#else
	// Run only filtered out tests
	::testing::GTEST_FLAG(filter) = "UnixSuite.*";
	#endif
	*/

	// Run only NOT filtered out tests
	//::testing::GTEST_FLAG(filter) = "-Win32Suite.*";
	
	::testing::GTEST_FLAG(output) = "xml:report.xml";
	
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
