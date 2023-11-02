
#include <scene/World.h>
#include <gtest/gtest.h>
#include <ray/Ray.h>

static World testWorld() {

	World w;

	Light l;
	l.position = Tuple::createPoint(-10, 10, -10);
	Sphere s1;
	s1.material.color = { 0.8, 1.0, 0.6 };
	s1.material.diffuse = 0.7f;
	s1.material.specular = 0.2f;

	Sphere s2(Mat4(1.0f).scale(0.5, 0.5, 0.5));

	w.lights.push_back(l);
	w.spheres.push_back(s1);
	w.spheres.push_back(s2);

	return w;
}


TEST(WorldTests, WorldInit) {
	World w;
	EXPECT_TRUE(w.lights.empty());
	EXPECT_TRUE(w.spheres.empty());
}

//TEST(WorldTests, WorldIntersection) {
//	World w = testWorld();
//
//	Ray r(Tuple::createPoint(0, 0, -5), Tuple::createVector(0, 0, 1));
//
//	auto intersections = w.intersectRay(r);
//	ASSERT_EQ(intersections.size(), 4);
//	intersections[0].t = 4.0f;
//	intersections[0].t = 4.5f;
//	intersections[0].t = 5.0f;
//	intersections[0].t = 6.0f;
//}