#include <ray/Ray.h>
#include <gtest/gtest.h>
#include <geometry/Sphere.h>
#include <ray/Intersection.h>
#include <ray/Precomputation.h>

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

TEST(RayTests, RayTransformations) {

	Ray r{ {1, 2, 3, 1}, {0, 1, 0, 0} };
	Mat4 trans = Mat4(1.0f).translate(3, 4, 5);

	auto translatedRay = r.transform(trans);

	EXPECT_EQ(translatedRay.origin, Tuple::createPoint(4, 6, 8));
	EXPECT_EQ(translatedRay.direction, Tuple::createVector(0, 1, 0));

	Mat4 scaleMatrix = Mat4(1.0f).scale(2, 3, 4);
	auto scaledRay = r.transform(scaleMatrix);

	EXPECT_EQ(scaledRay.origin, Tuple::createPoint(2, 6, 12));
	EXPECT_EQ(scaledRay.direction, Tuple::createVector(0, 3, 0));

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


TEST(IntersectionTests, IntersectionsWithScaledSphere) {

	Sphere s(Mat4::identity().scale(2,2,2));

	Ray r(Tuple::createPoint(0, 0, -5.0f), Tuple::createVector(0, 0, 1));

	auto intersections = r.findIntersections(s);

	ASSERT_EQ(intersections.size(), 2);
	EXPECT_EQ(intersections[0].t, 3);
	EXPECT_EQ(intersections[1].t, 7);

	Sphere s2(Mat4::identity().translate(5, 0, 0));
	auto intersections2 = r.findIntersections(s2);

	EXPECT_EQ(intersections2.size(), 0);
}


TEST(IntersectionTests, InteresectionPrecomputationOutsideSphere) {

	Ray r(Tuple::createPoint(0, 0, -5), Tuple::createVector(0, 0, 1));

	Sphere s;
	Intersection i(4, s);

	Precomputation p(i, r);

	EXPECT_EQ(p.t, i.t);
	EXPECT_EQ(p.s, i.s);
	EXPECT_EQ(p.point, Tuple::createPoint(0, 0, -1));
	EXPECT_EQ(p.eyeV, Tuple::createVector(0, 0, -1));
	EXPECT_EQ(p.normalV, Tuple::createVector(0, 0, -1));
	EXPECT_FALSE(p.inside);

}


TEST(IntersectionTests, InteresectionPrecomputationInsideSphere) {

	Ray r(Tuple::createPoint(0, 0, 0), Tuple::createVector(0, 0, 1));

	Sphere s;
	Intersection i(1, s);

	Precomputation p(i, r);

	EXPECT_EQ(p.t, i.t);
	EXPECT_EQ(p.s, i.s);
	EXPECT_TRUE(p.inside);
	EXPECT_EQ(p.point, Tuple::createPoint(0, 0, 1));
	EXPECT_EQ(p.eyeV, Tuple::createVector(0, 0, -1));
	EXPECT_EQ(p.normalV, Tuple::createVector(0, 0, -1));


}