#include <geometry/Plane.h>
#include <gtest/gtest.h>
#include <ray/Ray.h>


TEST(PlaneTests, PlaneNormalConstant) {

	Plane p;
	p.transform = Mat4(1.0f);

	EXPECT_EQ(p.normalAt(point(1, 0, 2)), vector(0, 1, 0));
	EXPECT_EQ(p.normalAt(point(2, 0, 1)), vector(0, 1, 0));
	EXPECT_EQ(p.normalAt(point(1.2, 2.5, 3.2)), vector(0, 1, 0));
}


TEST(PlaneTests, PlaneIntersection) {

	Ray r(
		point(0, 10, 0),
		vector(0, 0, 1)
	);

	Plane p;
	p.transform = Mat4(1.0f);

	EXPECT_EQ(p.intersectRay(r).size(), 0);

	Ray r2(point(0, 0, 0), vector(0, 0, 1));
	EXPECT_EQ(p.intersectRay(r2).size(), 0);


	Ray r3(point(0, 1, 0), vector(0, -1, 0));
	Intersections i1 = p.intersectRay(r3);
	ASSERT_EQ(i1.size(), 1);
	EXPECT_EQ(i1[0].t, 1.0f);
	EXPECT_EQ(i1[0].s, &p);

	Ray r4(point(0, -1, 0), vector(0, 1, 0));
	Intersections i2 = p.intersectRay(r4);
	ASSERT_EQ(i2.size(), 1);
	EXPECT_EQ(i2[0].t, 1.0f);
	EXPECT_EQ(i2[0].s, &p);


}