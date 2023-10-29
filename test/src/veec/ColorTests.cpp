#include <vec/Color.h>
#include <gtest/gtest.h>



TEST(ColorTests, ColorAddition) {
	Color c1{1.0f, 0.2f, 0.3f};
	Color c2{ 0.2f, 0.1f, 0.4f };
	EXPECT_EQ(c1 + c2, Color(1.2f, 0.3f, 0.7f));
}

TEST(ColorTests, ColorSubtraction) {
	Color c1{ 1.0f, 0.2f, 0.3f };
	Color c2{ 0.2f, 0.1f, 0.4f };
	EXPECT_EQ(c1 - c2, Color(0.8f, 0.1f, -0.1f));
}

TEST(ColorTests, ColorMultiplication) {
	Color c1{ 1.0f, 0.2f, 0.3f };
	Color c2{ 0.2f, 0.1f, 0.4f };
	EXPECT_EQ(c1 * c2, Color(0.2f, 0.02f, 0.12f));
}

TEST(ColorTests, ColorScalarMultiplication) {
	Color c1{ 1.0f, 0.2f, 0.3f };
	EXPECT_EQ(3 * c1, Color(3.0f, 0.6f, 0.9f));
}