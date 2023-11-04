#include <geometry/Sphere.h>
#include <gtest/gtest.h>
#include <linalg/Matrix.h>
#include <ray/Intersection.h>
#include <ray/Ray.h>

#define _USE_MATH_DEFINES
#include <math.h>


class TestShape : public Shape {

public:

	mutable Ray savedRay;

	Intersections localIntersect(const Ray& r) const override {
		savedRay = r;
		return {};
	};

	Tuple localNormalAt(const Tuple& t) const override {
		return vector(t.x, t.y, t.z);
	};
};

TEST(ShapeTests, ShapeInit) {
	TestShape s;

	Material m;

	m.ambient = 1.0f;
	s.material = m;

	EXPECT_EQ(s.material, m);
	EXPECT_EQ(s.transform, Mat4::identity());
}

TEST(ShapeTests, ShapeIntersectionLocalRay) {


	Ray r(point(0, 0, -5), vector(0, 0, 1));
	TestShape s;

	s.transform = Mat4(1.0f).scale(2, 2, 2);
	s.intersectRay(r);

	EXPECT_EQ(s.savedRay.origin, point(0, 0, -2.5));
	EXPECT_EQ(s.savedRay.direction, vector(0, 0, 0.5));
	

	s.transform = Mat4(1.0f).translate(5, 0, 0);
	s.intersectRay(r);

	EXPECT_EQ(s.savedRay.origin, point(-5, 0, -5));
	EXPECT_EQ(s.savedRay.direction, vector(0, 0, 1));
}

TEST(ShapeTests, ShapeNormalAtLocalRay) {
	TestShape s;
	s.transform = Mat4(1.0f).translate(0, 1, 0);

	Tuple n = s.normalAt(point(0, 1.70711, -0.70711));
	EXPECT_EQ(n, vector(0, 0.70711, -0.70711));

	s.transform = Mat4(1.0f).rotate(0, 0, M_PI / 5.0f).scale(1, 0.5, 1);
	Tuple n1 = s.normalAt(point(0, sqrtf(2) / 2.0f, -sqrtf(2) / 2.0f));
	EXPECT_EQ(n1, vector(0, 0.97014, -0.24254));
}


TEST(SphereTests, SphereNormalAt) {

	Sphere s;

	EXPECT_EQ(s.normalAt(Tuple::createPoint(1, 0, 0)), Tuple::createVector(1, 0, 0));
	EXPECT_EQ(s.normalAt(Tuple::createPoint(0, 1, 0)), Tuple::createVector(0, 1, 0));
	EXPECT_EQ(s.normalAt(Tuple::createPoint(0, 0, 1)), Tuple::createVector(0, 0, 1));

	float root3Over3 = sqrtf(3.0f) / 3.0f;
	auto p = Tuple::createPoint(root3Over3, root3Over3, root3Over3);

	EXPECT_EQ(s.normalAt(p), Tuple::createVector(root3Over3, root3Over3, root3Over3));
	EXPECT_EQ(s.normalAt(p), s.normalAt(p).normalized());

}

TEST(SphereTests, SphereNormalTransformation) {

	Sphere s{ Mat4(1.0f).translate(0, 1, 0)};

	Tuple n = s.normalAt(Tuple::createPoint(0, 1.70711f, -0.70711f));

	EXPECT_EQ(n, Tuple::createVector(0, 0.70711, -0.70711));

	s.transform = Mat4(1.0f).rotate(0, 0, M_PI / 5.0f).scale(1.0f, 0.5f, 1.0f);

	EXPECT_EQ(s.normalAt(Tuple::createPoint(0, sqrtf(2) / 2.0f, -sqrtf(2) / 2.0f)), Tuple::createVector(0, 0.97014f, -0.24254f));

}
