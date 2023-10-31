#include <ray/Ray.h>
#include <gtest/gtest.h>
#include <geometry/Sphere.h>
#include <ray/Intersection.h>

TEST(RayTests, RayInit) {

	Tuple o = Tuple::createPoint(0, 2, 3);
	Tuple d = Tuple::createVector(0, 1, 4);

	Ray r{ o, d };

	EXPECT_EQ(r.origin, o);
	EXPECT_EQ(r.direction, d);
}


TEST(RayTests, RayPositionAt) {

	Tuple o = Tuple::createPoint(0, 2, 3);
	Tuple d = Tuple::createVector(0, 1, 4);

	Ray r(o, d);

	EXPECT_EQ(r.positionAt(0), o);
	EXPECT_EQ(r.positionAt(1), Tuple::createPoint(0, 3, 7));
	EXPECT_EQ(r.positionAt(3), Tuple::createPoint(0, 5, 15));
	EXPECT_EQ(r.positionAt(-1.0f), Tuple::createPoint(0, 1, -1));
	EXPECT_EQ(r.positionAt(0.5f), Tuple::createPoint(0, 2.5f, 5.0f));
}


TEST(RayTests, RaySphereIntersection2Points) {
	Ray r{ {0, 0, -5, 1} , { 0, 0, 1, 0 } };
	Sphere s;

	auto intersections = r.findIntersections(s);

	ASSERT_EQ(intersections.size(), 2);
	EXPECT_EQ(intersections[0].t, 4.0f);
	EXPECT_EQ(intersections[1].t, 6.0f);
}

TEST(RayTests, RaySphereIntersectionTangent) {
	Ray r{ {0, 1, -5, 1} , { 0, 0, 1, 0 } };
	Sphere s;

	auto intersections = r.findIntersections(s);

	ASSERT_EQ(intersections.size(), 2);
	EXPECT_EQ(intersections[0].t, 5.0f);
	EXPECT_EQ(intersections[1].t, 5.0f);
}

TEST(RayTests, RayMissesSphere) {
	Ray r{ {0, 2, -5, 1} , { 0, 0, 1, 0 } };
	Sphere s;

	auto intersections = r.findIntersections(s);

	ASSERT_EQ(intersections.size(), 0);
}

TEST(RayTests, RayInsideSphereIntersection) {
	Ray r{ {0, 0, 0, 1} , { 0, 0, 1, 0 } };
	Sphere s;

	std::vector<Intersection> intersections = r.findIntersections(s);

	ASSERT_EQ(intersections.size(), 2);
	EXPECT_EQ(intersections[0].t, -1.0f);
	EXPECT_EQ(intersections[1].t, 1.0f);
}

TEST(RayTests, RayInfrontOfSphereIntersection) {
	Ray r{ {0, 0, 5, 1} , { 0, 0, 1, 0 } };
	Sphere s;

	std::vector<Intersection> intersections = r.findIntersections(s);

	ASSERT_EQ(intersections.size(), 2);
	EXPECT_EQ(intersections[0].t, -6.0f);
	EXPECT_EQ(intersections[1].t, -4.0f);
}


TEST(IntersectionTests, IntersectionsHit) {

	Sphere s;

	using Intersections = std::vector<Intersection>;

	Intersections allPositives{
		{1, s}, {2, s}, {3, s}
	};

	EXPECT_EQ(findHit(allPositives)->t, 1.0f);

	Intersections someNegative{
		{5, s}, {2, s}, {-1, s}
	};

	EXPECT_EQ(findHit(someNegative)->t, 2.0f);

	Intersections allNegatives{
		{-1, s}, {-5, s}, {-10, s}
	};

	EXPECT_EQ(findHit(allNegatives), allNegatives.end());

}