# Run only filtered
./build/test_runner --gtest_filter="UnixSuite.*"

# Run only NOT filtered
./build/test_runner --gtest_filter="-Win32Suite.*"
