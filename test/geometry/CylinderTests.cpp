#include <geometry/Cylinder.h>
#include <gtest/gtest.h>


TEST(CylinderTests, RayMissesCylinder) {


	Cylinder c;

	{
		Ray r(point(1, 0, 0), vector(0, 1, 0).normalized());
		auto intersections = c.intersectRay(r);
		EXPECT_EQ(intersections.size(), 0);
	}

	{
		Ray r(point(0, 0, 0), vector(0, 1, 0).normalized());
		auto intersections = c.intersectRay(r);
		EXPECT_EQ(intersections.size(), 0);
	}

	{
		Ray r(point(0, 0, -5), vector(1, 1, 1).normalized());
		auto intersections = c.intersectRay(r);
		EXPECT_EQ(intersections.size(), 0);
	}

}


TEST(CylinderTests, RayHitsCylinder) {

	Cylinder c;

	{
		Ray r(point(1, 0, -5), vector(0, 0, 1).normalized());
		auto intersections = c.intersectRay(r);
		ASSERT_EQ(intersections.size(), 2);
		EXPECT_EQ(intersections[0].t, 5);
		EXPECT_EQ(intersections[1].t, 5);
	}

	{
		Ray r(point(0, 0, -5), vector(0, 0, 1).normalized());
		auto intersections = c.intersectRay(r);
		ASSERT_EQ(intersections.size(), 2);
		EXPECT_TRUE(compareFloats(intersections[0].t, 4));
		EXPECT_TRUE(compareFloats(intersections[1].t, 6));
	}

	{
		Ray r(point(0.5, 0, -5), vector(0.1, 1, 1).normalized());
		auto intersections = c.intersectRay(r);
		ASSERT_EQ(intersections.size(), 2);
		EXPECT_TRUE(compareFloats(intersections[0].t, 6.80798));
		EXPECT_TRUE(compareFloats(intersections[1].t, 7.08872f));
	}

}

TEST(CylinderTests, CylinderNormal) {
	
	Cylinder c;

	{
		Tuple n = c.normalAt(point(1, 0, 0));
		EXPECT_EQ(n, vector(1, 0, 0));
	}

	{
		Tuple n = c.normalAt(point(0, 5, -1));
		EXPECT_EQ(n, vector(0, 0, -1));
	}

	{
		Tuple n = c.normalAt(point(0, -2, 1));
		EXPECT_EQ(n, vector(0, 0, 1));
	}

	{
		Tuple n = c.normalAt(point(-1, 1, 0));
		EXPECT_EQ(n, vector(-1, 0, 0));
	}

}

TEST(CylinderTests, TruncatedCylinderIntersection) {

	{
		Cylinder c;
		c.minimum = 1;
		c.maximum = 2;

		Ray r(point(0, 1.5, 0), vector(0.1, 1, 0));
		auto intersections = c.intersectRay(r);
		EXPECT_EQ(intersections.size(), 0);
	}

	{
		Cylinder c;
		c.minimum = 1;
		c.maximum = 2;

		Ray r(point(0, 3, -5), vector(0, 0, 1));
		auto intersections = c.intersectRay(r);
		EXPECT_EQ(intersections.size(), 0);
	}

	{
		Cylinder c;
		c.minimum = 1;
		c.maximum = 2;

		Ray r(point(0, 0, -5), vector(0, 0, 1));
		auto intersections = c.intersectRay(r);
		EXPECT_EQ(intersections.size(), 0);
	}

	{
		Cylinder c;
		c.minimum = 1;
		c.maximum = 2;

		Ray r(point(0, 2, -5), vector(0, 0, 1));
		auto intersections = c.intersectRay(r);
		EXPECT_EQ(intersections.size(), 0);
	}

	{
		Cylinder c;
		c.minimum = 1;
		c.maximum = 2;

		Ray r(point(0, 1, -5), vector(0, 0, 1));
		auto intersections = c.intersectRay(r);
		EXPECT_EQ(intersections.size(), 0);
	}

	{
		Cylinder c;
		c.minimum = 1;
		c.maximum = 2;

		Ray r(point(0, 1.5, -2), vector(0, 0, 1));
		auto intersections = c.intersectRay(r);
		EXPECT_EQ(intersections.size(), 2);
	}


}


TEST(CylinderTests, RayIntersectsCap) {


	{
		Cylinder c;
		c.closed = true;
		c.minimum = 1;
		c.maximum = 2;

		auto direction = vector(0, -1, 0).normalized();
		auto origin = point(0, 3, 0);

		Ray r(origin, direction);

		auto intersections = c.intersectRay(r);
		ASSERT_EQ(intersections.size(), 2);
	}

	{
		Cylinder c;
		c.closed = true;
		c.minimum = 1;
		c.maximum = 2;

		auto direction = vector(0, -1, 2).normalized();
		auto origin = point(0, 3, -2);

		Ray r(origin, direction);

		auto intersections = c.intersectRay(r);
		ASSERT_EQ(intersections.size(), 2);
	}

	{
		Cylinder c;
		c.closed = true;
		c.minimum = 1;
		c.maximum = 2;

		auto direction = vector(0, -1, 1).normalized();
		auto origin = point(0, 4, -2);

		Ray r(origin, direction);

		auto intersections = c.intersectRay(r);
		ASSERT_EQ(intersections.size(), 2);
	}

	{
		Cylinder c;
		c.closed = true;
		c.minimum = 1;
		c.maximum = 2;

		auto direction = vector(0, 1, 2).normalized();
		auto origin = point(0, 0, -2);

		Ray r(origin, direction);

		auto intersections = c.intersectRay(r);
		ASSERT_EQ(intersections.size(), 2);
	}

	{
		Cylinder c;
		c.closed = true;
		c.minimum = 1;
		c.maximum = 2;

		auto direction = vector(0, 1, 1).normalized();
		auto origin = point(0, -1, -2);

		Ray r(origin, direction);

		auto intersections = c.intersectRay(r);
		ASSERT_EQ(intersections.size(), 2);
	}

}