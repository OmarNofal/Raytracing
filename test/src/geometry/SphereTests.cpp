#include <geometry/Sphere.h>
#include <gtest/gtest.h>
#include <linalg/Matrix.h>


TEST(SphereTests, SphereInit) {
	Sphere s;

	EXPECT_EQ(s.transform, Mat4::identity());
}
