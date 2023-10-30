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


TEST(TupleTests, PointPlusVectorIsPoint) {
	auto point = Tuple::createPoint(1.0f, 2.0f, 3.0f);
	auto vector = Tuple::createVector(2.0f, 1.0f, 0.1f);

	auto newPoint = point + vector;

	EXPECT_TRUE(newPoint == Tuple::createPoint(3.0f, 3.0f, 3.1f));
	EXPECT_TRUE(newPoint.isPoint());
}

TEST(TupleTests, PointMinusVectorIsPoint) {
	auto point = Tuple::createPoint(1.0f, 2.0f, 3.0f);
	auto vector = Tuple::createVector(2.0f, 1.0f, 0.1f);

	auto newPoint = point - vector;

	EXPECT_TRUE(newPoint == Tuple::createPoint(-1.0f, 1.0f, 2.9f));
	EXPECT_TRUE(newPoint.isPoint());
}

TEST(TupleTests, VectorMinusVectorIsVector) {
	auto vector1 = Tuple::createVector(1.0f, 2.0f, 3.0f);
	auto vector2 = Tuple::createVector(2.0f, 1.0f, 0.1f);

	auto newVector = vector1 - vector2;

	EXPECT_TRUE(newVector == Tuple::createVector(-1.0f, 1.0f, 2.9f));
	EXPECT_TRUE(newVector.isVector());
}

TEST(TupleTests, PointNegation) {
	EXPECT_TRUE( (- Tuple::createPoint(1.0f, 0.0f, -2.0f)) == Tuple(-1.0f, 0.0f, 2.0f, -1.0f));
}

TEST(TupleTests, VectorNegation) {
	EXPECT_TRUE((- Tuple::createVector(-1.0f, 1.0f, -2.0f)) == Tuple::createVector(1.0f, -1.0f, 2.0f));
}

TEST(TupleTests, TupleScalarMult) {
	EXPECT_EQ(Tuple(1.0f, 3.0f, 2.2f, 4.0f) * 0.5f, Tuple(0.5f, 1.5f, 1.1f, 2.0f));
	EXPECT_EQ(Tuple(1.0f, 3.0f, 2.2f, 4.0f) * 2.0f, Tuple(2.0f, 6.0f, 4.4f, 8.0f));
}

TEST(TupleTests, TupleMagnitude) {
	EXPECT_EQ(Tuple(1.0f, 0.0f, 0.0f, 0.0f).magnitude(), 1.0f);
	EXPECT_EQ(Tuple(0.0f, 1.0f, 0.0f, 0.0f).magnitude(), 1.0f);
	EXPECT_EQ(Tuple(0.0f, 0.0f, 1.0f, 0.0f).magnitude(), 1.0f);
	EXPECT_EQ(Tuple(0.0f, 0.0f, 0.0f, 1.0f).magnitude(), 1.0f);
	EXPECT_EQ(Tuple(1.0f, 2.0f, 0.0f, 0.0f).magnitude(), sqrtf(5.0f));
	EXPECT_EQ(Tuple(-1.0f, -2.0f, -3.0f, 0.0f).magnitude(), sqrtf(14.0f));
}

TEST(TupleTests, TupleNormalization) {
	EXPECT_EQ(Tuple(4.0f, 0.0f, 0.0f, 0.0f).normalized(), Tuple(1.0f));
	auto sqrt14 = sqrtf(14.0f);
	EXPECT_EQ(Tuple(1.0f, 2.0f, 3.0f, 0.0f).normalized(), Tuple(1.0f/sqrt14, 2.0f/sqrt14, 3.0f/sqrt14));
}

TEST(TupleTests, DotProduct) {
	auto v1 = Tuple::createVector(1, 2, 3);
	auto v2 = Tuple::createVector(2, 3, 4);
	EXPECT_EQ(v1.dot(v2), 20);
}

TEST(TupleTests, CrossProduct) {
	auto v1 = Tuple::createVector(1, 2, 3);
	auto v2 = Tuple::createVector(2, 3, 4);
	EXPECT_EQ(v1.cross(v2), Tuple::createVector(-1, 2, -1));
	EXPECT_EQ(v2.cross(v1), Tuple::createVector(1, -2, 1));
}