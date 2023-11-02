#include <geometry/Sphere.h>
#include <gtest/gtest.h>
#include <linalg/Matrix.h>

#define _USE_MATH_DEFINES
#include <math.h>

TEST(SphereTests, SphereInit) {
	Sphere s;
	Material m;

	m.ambient = 1.0f;
	s.material = m;

	EXPECT_EQ(s.material, m);
	EXPECT_EQ(s.transform, Mat4::identity());
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
