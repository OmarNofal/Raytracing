#include <geometry/Cube.h>
#include <gtest/gtest.h>



TEST(CubeTests, RayIntersectsCube) {

	Cube c;

	
	
	Ray r1(
		point(5, 0.5, 0),
		vector(-1, 0, 0)
	);

	auto xs1 =
		c.intersectRay(r1);
	EXPECT_EQ(xs1[0].t, 4.0f);
	EXPECT_EQ(xs1[1].t, 6.0f);



	Ray r2(
		point(-5, 0.5, 0),
		vector(1, 0, 0)
	);

	auto xs2 =
		c.intersectRay(r2);
	EXPECT_EQ(xs2[0].t, 4.0f);
	EXPECT_EQ(xs2[1].t, 6.0f);



	Ray r3(
		point(0.5, 5, 0),
		vector(0, -1, 0)
	);

	auto xs3 =
		c.intersectRay(r3);
	EXPECT_EQ(xs3[0].t, 4.0f);
	EXPECT_EQ(xs3[1].t, 6.0f);



	Ray r4(
		point(0.5, -5, 0),
		vector(0, 1, 0)
	);

	auto xs4 =
		c.intersectRay(r4);
	EXPECT_EQ(xs4[0].t, 4.0f);
	EXPECT_EQ(xs4[1].t, 6.0f);



	Ray r5(
		point(0.5, 0, 5),
		vector(0, 0, -1)
	);

	auto xs5 =
		c.intersectRay(r5);
	EXPECT_EQ(xs5[0].t, 4.0f);
	EXPECT_EQ(xs5[1].t, 6.0f);



	Ray r6(
		point(0.5, 0, -5),
		vector(0, 0, 1)
	);

	auto xs6 =
		c.intersectRay(r6);
	EXPECT_EQ(xs6[0].t, 4.0f);
	EXPECT_EQ(xs6[1].t, 6.0f);



	Ray r7(
		point(0, 0.5, 0),
		vector(0, 0, 1)
	);

	auto xs7 =
		c.intersectRay(r7);
	EXPECT_EQ(xs7[0].t, -1.0f);
	EXPECT_EQ(xs7[1].t, 1.0f);



}


TEST(CubeTests, RayMissesCube) {

	Cube c;

	{
		Ray r(
			point(-2, 0, 0),
			vector(0.2673, 0.5345, 0.8018)
		);
		EXPECT_EQ(c.intersectRay(r).size(), 0);
	}
	{
		Ray r(
			point(0, -2, 0),
			vector(0.8018, 0.2673, 0.5345)
		);
		EXPECT_EQ(c.intersectRay(r).size(), 0);
	}
	{
		Ray r(
			point(0, 0, -2),
			vector(0.5345, 0.8018, 0.2673)
		);
		EXPECT_EQ(c.intersectRay(r).size(), 0);
	}
	{
		Ray r(
			point(2, 0, 2),
			vector(0, -1, 0)
		);
		EXPECT_EQ(c.intersectRay(r).size(), 0);
	}
	{
		Ray r(
			point(2, 2, 0),
			vector(-1, 0, 0)
		);
		EXPECT_EQ(c.intersectRay(r).size(), 0);
	}

}


TEST(CubeTests, CubeNormals) {

	Cube c;

	{
		Tuple p = point(1, 0.5, -0.8);
		EXPECT_EQ(c.normalAt(p), vector(1, 0, 0));
	}
	{
		Tuple p = point(-1, -0.2, 0.9);
		EXPECT_EQ(c.normalAt(p), vector(-1, 0, 0));
	}
	{
		Tuple p = point(-0.4, 1, -0.1);
		EXPECT_EQ(c.normalAt(p), vector(0, 1, 0));
	}
	{
		Tuple p = point(0.3, -1, -0.7);
		EXPECT_EQ(c.normalAt(p), vector(0, -1, 0));
	}
	{
		Tuple p = point(-0.6, 0.3, 1);
		EXPECT_EQ(c.normalAt(p), vector(0, 0, 1));
	}
	{
		Tuple p = point(0.4, 0.4, -1);
		EXPECT_EQ(c.normalAt(p), vector(0, 0, -1));
	}
	{
		Tuple p = point(1, 1, 1);
		EXPECT_EQ(c.normalAt(p), vector(1, 0, 0));
	}
	{
		Tuple p = point(-1, -1, -1);
		EXPECT_EQ(c.normalAt(p), vector(-1, 0, 0));
	}
}