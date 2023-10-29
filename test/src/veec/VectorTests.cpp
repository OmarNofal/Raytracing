#include <vec/Tuple.h>
#include <gtest/gtest.h>
#include <utils/FloatUtils.h>


TEST(TupleTests, VectorInit) {
	Tuple vec{1.2f, 2.3f, 3.4f, 1.0f};

	EXPECT_TRUE(compareFloats(vec.x, 1.2f));
	EXPECT_TRUE(compareFloats(vec.y, 2.3f));
	EXPECT_TRUE(compareFloats(vec.z, 3.4f));
}


TEST(TupleTests, TupleIsPointTrue) {
	auto point = Tuple::createPoint(0.0f, 1.0f, 2.0f);
	EXPECT_TRUE(point.isPoint());
	EXPECT_FALSE(point.isVector());
}

TEST(TupleTests, TupleIsVectorTrue) {
	auto vec = Tuple::createVector(0.0f, 1.0f, 2.0f);
	EXPECT_TRUE(vec.isVector());
	EXPECT_FALSE(vec.isPoint());
}
