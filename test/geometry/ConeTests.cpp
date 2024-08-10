#include <geometry/Cone.h>
#include <ray/Ray.h>
#include <gtest/gtest.h>


TEST(ConeTests, RayIntersects) {
	
	Cone c;

	{
		auto origin = point(0, 0, -5);
		auto direction = vector(0, 0, 1).normalized();

		Ray r(origin, direction);

		auto xs = c.intersectRay(r);

		EXPECT_EQ(xs.size(), 2);
		EXPECT_EQ(xs[0].t, 5);
		EXPECT_EQ(xs[1].t, 5);
	}

	{
		auto origin = point(0, 0, -4.9999f);
		auto direction = vector(1, 1, 1).normalized();

		Ray r(origin, direction);

		auto xs = c.intersectRay(r);

		EXPECT_EQ(xs.size(), 2);
		
		EXPECT_TRUE(compareFloats(xs[0].t, 8.66025f));
		EXPECT_TRUE(compareFloats(xs[1].t, 8.66025f));
		
	}

	{
		auto origin = point(1, 1, -5);
		auto direction = vector(-0.5, -1, 1).normalized();

		Ray r(origin, direction);

		auto xs = c.intersectRay(r);

		EXPECT_EQ(xs.size(), 2);
		EXPECT_TRUE(compareFloats(xs[0].t, 4.55006f));
		EXPECT_TRUE(compareFloats(xs[1].t, 49.44994f));
	}

}

TEST(ConeTests, RayParallelIntersect) {

	Cone c;

	auto direction = vector(0, 1, 1).normalized();
	Ray r(point(0, 0, -1), direction);

	Intersections xs = c.intersectRay(r);
	
	EXPECT_EQ(xs.size(), 1);
	EXPECT_TRUE(compareFloats(xs[0].t, 0.35355));
}

TEST(ConeTests, IntersectionEndCaps) {

	Cone c;
	c.minimum = -0.5;
	c.maximum = 0.5;
	c.closed = true;

	{
		auto direction = vector(0, 1, 0).normalized();
		Ray r(point(0, 0, -5), direction);

		auto xs = c.intersectRay(r);
		EXPECT_EQ(xs.size(), 0);
	}
	
	{
		auto direction = vector(0, 1, 1).normalized();
		Ray r(point(0, 0, -0.25), direction);

		auto xs = c.intersectRay(r);
		EXPECT_EQ(xs.size(), 2);
	}

	{
		auto direction = vector(0, 1, 0).normalized();
		Ray r(point(0, 0, -0.25), direction);

		auto xs = c.intersectRay(r);
		EXPECT_EQ(xs.size(), 4);
	}

}


TEST(ConeTests, NormalTests) {

	Cone c;


	{
		Tuple n = c.normalAt(point(1, 1, 1));
		EXPECT_EQ(n, vector(1, -sqrtf(2), 1).normalized());
	}

	{
		Tuple n = c.normalAt(point(-1, -1, 0));
		EXPECT_EQ(n, vector(-1, 1, 0).normalized());
	}
}