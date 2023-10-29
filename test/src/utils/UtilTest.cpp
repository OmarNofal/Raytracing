#include <gtest/gtest.h>
#include <utils/FloatUtils.h>

TEST(UtilTests, CompareFloatEqualTest) {
	EXPECT_TRUE(compareFloats(0.012f, 0.01201f));
}

TEST(UtilTests, CompareFloatNotEqualTest) {
	EXPECT_FALSE(compareFloats(0.012f, 0.013f));
}