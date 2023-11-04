
#include <scene/World.h>
#include <gtest/gtest.h>
#include <ray/Ray.h>
#include <ray/Precomputation.h>

static World testWorld() {

	World w;

	Light l;
	l.position = Tuple::createPoint(-10, 10, -10);
	l.intensity = Color(1.0f, 1.0f, 1.0f);
	Sphere s1;
	s1.transform = Mat4(1.0f);
	s1.material.color = Color(0.8, 1.0, 0.6);
	s1.material.diffuse = 0.7f;
	s1.material.specular = 0.2f;

	Sphere s2(Mat4(1.0f).scale(0.5, 0.5, 0.5));

	w.lights.push_back(l);
	w.shapes.push_back(s1);
	w.shapes.push_back(s2);

	return w;
}


TEST(WorldTests, WorldInit) {
	World w;
	EXPECT_TRUE(w.lights.empty());
	EXPECT_TRUE(w.shapes.empty());
}

TEST(WorldTests, WorldIntersection) {
	World w = testWorld();

	Ray r(Tuple::createPoint(0, 0, -5), Tuple::createVector(0, 0, 1));

	auto intersections = w.intersectRay(r);
	ASSERT_EQ(intersections.size(), 4);
	EXPECT_EQ(intersections[0].t, 4.0f);
	EXPECT_EQ(intersections[1].t, 4.5f);
	EXPECT_EQ(intersections[2].t, 5.5f);
	EXPECT_EQ(intersections[3].t, 6.0f);
}

TEST(WorldTests, IntersectionShadingOutside) {

	World w = testWorld();

	Ray r(Tuple::createPoint(0, 0, -5), Tuple::createVector(0, 0, 1));
	const Sphere& s = w.shapes[0];

	Intersection i(4, &s);

	Precomputation p(i, r);

	Color c = w.shadeHit(p);

	EXPECT_EQ(c, Color(0.38066f, 0.47583f, 0.2855f));
}

TEST(WorldTests, IntersectionShadingInside) {

	World w = testWorld();
	w.lights.clear();
	w.lights.push_back(Light(Tuple::createPoint(0, 0.25, 0)));

	Ray r(Tuple::createPoint(0, 0, 0), Tuple::createVector(0, 0, 1));
	const Sphere& s = w.shapes[1];

	Intersection i(0.5, &s);

	Precomputation p(i, r);

	Color c = w.shadeHit(p);

	EXPECT_EQ(c, Color(0.90498f, 0.90498f, 0.90498f));
}


TEST(WorldTests, ColorAt) {

	World w = testWorld();

	Ray r(Tuple::createPoint(0, 0, -5), Tuple::createVector(0, 1, 0));

	Color c = w.colorAt(r);

	EXPECT_EQ(c, Color(0, 0, 0));

	Ray r2(
		Tuple::createPoint(0, 0, -5),
		Tuple::createVector(0, 0, 1)
	);
	
	Color c2 = w.colorAt(r2);

	EXPECT_EQ(c2, Color(0.38066, 0.47583, 0.2855));


	// Inside outer but outside inner

	Ray r3(
		Tuple::createPoint(0, 0, 0.75),
		Tuple::createVector(0, 0, -1)
	);

	w.shapes[1].material.ambient = 1.0f;

	Color c3 = w.colorAt(r3);
	EXPECT_EQ(c3, w.shapes[1].material.color);

}


TEST(ShadowTests, IsInShadow) {

	World w = testWorld();
	const Light& l = w.lights[0];

	Tuple p1 = Tuple::createPoint(0, 10, 0);
	EXPECT_FALSE(w.isPointInShadow(p1, l));

	Tuple p2 = Tuple::createPoint(10, -10, 10);
	EXPECT_TRUE(w.isPointInShadow(p2, l));

	Tuple p3 = Tuple::createPoint(-20, 20, -20);
	EXPECT_FALSE(w.isPointInShadow(p3, l));

	Tuple p4 = Tuple::createPoint(-2, 2, -2);
	EXPECT_FALSE(w.isPointInShadow(p4, l));


}

TEST(ShadowTests, ShadeShadow) {

	World w;
	Light l(Tuple::createPoint(0, 0, -10));
	w.lights.push_back(l);

	Sphere s1;
	Sphere s2;
	s2.transform = Mat4(1.0f).translate(0, 0, 10);

	w.shapes.push_back(s1);
	w.shapes.push_back(s2);

	Ray r(Tuple::createPoint(0, 0, 5), Tuple::createVector(0, 0, 1));

	Intersection i(4, &s2);

	auto p = Precomputation(i, r);
	auto c = w.shadeHit(p);

	EXPECT_EQ(c, Color(0.1, 0.1, 0.1));

}
