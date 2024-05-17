
#include <scene/World.h>
#include <gtest/gtest.h>
#include <ray/Ray.h>
#include <ray/Precomputation.h>
#include <geometry/Plane.h>
#include <algorithm>


Sphere s1;
Sphere s2(Mat4(1.0f).scale(0.5, 0.5, 0.5));

static World testWorld() {

	World w;

	s1.transform = Mat4(1.0f);
	s1.material.color = Color(0.8, 1.0, 0.6);
	s1.material.diffuse = 0.7f;
	s1.material.specular = 0.2f;

	Light l;
	l.position = Tuple::createPoint(-10, 10, -10);
	l.intensity = Color(1.0f, 1.0f, 1.0f);
	

	w.lights.push_back(l);
	w.shapes.push_back(&s1);
	w.shapes.push_back(&s2);

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
	const Shape& s = *w.shapes[0];

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
	const Shape& s = *w.shapes[1];

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

	w.shapes[1]->material.ambient = 1.0f;

	Color c3 = w.colorAt(r3);
	EXPECT_EQ(c3, w.shapes[1]->material.color);

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

	w.shapes.push_back(&s1);
	w.shapes.push_back(&s2);

	Ray r(Tuple::createPoint(0, 0, 5), Tuple::createVector(0, 0, 1));

	Intersection i(4, &s2);

	auto p = Precomputation(i, r);
	auto c = w.shadeHit(p);

	EXPECT_EQ(c, Color(0.1, 0.1, 0.1));

}


TEST(ReflectionTests, ReflectAgainstNonReflective) {

	World w = testWorld();


	Ray r(Tuple::createPoint(0, 0, 0), Tuple::createVector(0, 0, 1));

	Intersection i(1, w.shapes[1]);

	auto p = Precomputation(i, r);
	auto c = w.shadeHit(p);

	EXPECT_EQ(w.reflectedColor(p), Color::black());

}


TEST(ReflectionTests, ReflectAgainstReflective) {

	World w = testWorld();

	Plane p;
	p.transform = Mat4(1.0f).translate(0, -1, 0);
	p.material.reflective = 0.5f;

	w.shapes.push_back(&p);

	float root2 = sqrtf(2.0f);
	Ray r(Tuple::createPoint(0, 0, -3), Tuple::createVector(0, -root2 / 2.0f, root2 / 2.0f));

	Intersection i(root2, &p);

	auto pc = Precomputation(i, r);

	EXPECT_EQ(w.reflectedColor(pc), Color(0.19032f, 0.2379f, 0.14274f));
	EXPECT_EQ(w.shadeHit(pc), Color(0.87677f, 0.92436f, 0.82918f));
}


TEST(ReflectionTests, InfiniteRecursion) {

	World w;
	
	Plane p1;
	p1.material.reflective = 1.0f;
	p1.transform = Mat4(1.0f).translate(0, 1, 0);

	Plane p2;
	p2.material.reflective = 1.0f;
	p2.transform = Mat4(1.0f).translate(0, -1, 0);

	w.shapes.push_back(&p1);
	w.shapes.push_back(&p2);


	Ray r(point(0, 0, 0), vector(0, 1, 0));
	
	w.colorAt(r);
}


Sphere glassSphere() {
	Sphere s;
	s.material.transperancy = 1.0f;
	s.material.refractiveIndex = 1.5f;

	return s;
}

TEST(RefractionTests) {


	Sphere A = glassSphere();
	A.transform = Mat4(1.0f).scale(2, 2, 2);

	Sphere B = glassSphere();
	B.transform = Mat4(1.0f).translate(0, 0, -0.25f);
	B.material.refractiveIndex = 2.0f;

	Sphere C = glassSphere();
	C.transform = Mat4(1.0f).translate(0, 0, 0.25f);
	C.material.refractiveIndex = 2.5f;

	Ray r(point(0,0,-4), vector(0, 0, 1));

	std::vector<Intersection> intersections =
	{
		Intersection(2, &A),
		Intersection(2.75, &B),
		Intersection(3.25, &C),
		Intersection(4.75, &B),
		Intersection(5.25, &C),
		Intersection(6, &A)
	};

	Precomputation p0(intersections[0], r, intersections);
	Precomputation p1(intersections[1], r, intersections);
	Precomputation p2(intersections[2], r, intersections);
	Precomputation p3(intersections[3], r, intersections);
	Precomputation p4(intersections[4], r, intersections);
	Precomputation p5(intersections[5], r, intersections);

	EXPECT_EQ(p0.n1, 1.0f);
	EXPECT_EQ(p0.n2, 1.5f);

	EXPECT_EQ(p1.n1, 1.5f);
	EXPECT_EQ(p1.n2, 2.0f);

	EXPECT_EQ(p2.n1, 2.0f);
	EXPECT_EQ(p2.n2, 2.5f);

	EXPECT_EQ(p3.n1, 2.5f);
	EXPECT_EQ(p3.n2, 2.5f);

	EXPECT_EQ(p4.n1, 2.5f);
	EXPECT_EQ(p4.n2, 1.5f);

	EXPECT_EQ(p5.n1, 1.5f);
	EXPECT_EQ(p5.n2, 1.0f);

}

TEST(RefractionTests, ComputingUnderpoint) {

	Ray r(point(0, 0, -5), vector(0, 0, 1));

	Sphere s = glassSphere();
	s.transform = Mat4(1.0f).translate(0, 0, 1);

	Intersection i{ 5, &s };
	Intersections xs{i};

	Precomputation p(i, r, xs);
	EXPECT_GT(p.underPoint.z, EPSILON / 2.0f);
	EXPECT_LT(p.point.z, p.underPoint.z);
}

TEST(RefractionTests, RefractedColorOpaque) {

	World w = testWorld();

	Shape& s = *w.shapes[0];

	Ray r(point(0, 0, -5), vector(0, 0, 1));
	Intersections xs{ Intersection(4, &s), Intersection(6, &s)};

	Precomputation p(xs[0], r, xs);
	EXPECT_EQ(w.refractedColor(p, 5), Color::black());
}

TEST(RefractionTests, RefractedColorTIR) {

	World w = testWorld();

	Shape& s = *w.shapes[0];
	s.material.transperancy = 1.0f;
	s.material.refractiveIndex = 1.5f;

	float root2 = sqrtf(2.0f);

	Ray r(point(0, 0, root2 / 2.0f), vector(0, 1, 0));
	Intersections xs{ Intersection(-root2 / 2.0f, &s), Intersection(root2/2.0f, &s) };

	Precomputation p(xs[1], r, xs);
	EXPECT_EQ(w.refractedColor(p, 5), Color::black());
}


TEST(RefractionTests, RefractionShadeHit) {

	World w = testWorld();

	Shape& A = *w.shapes[0];
	A.material.ambient = 1.0f;

	Plane p;
	p.transform = Mat4(1.0f).translate(0, -1, 0);
	p.material.transperancy = 0.5f;
	p.material.refractiveIndex = 1.5f;

	w.shapes.push_back(&p);

	Sphere s;
	s.material.color = Color(1, 0, 0);
	s.material.ambient = 0.5f;
	s.transform = Mat4(1.0f).translate(0, -3.5f, -0.5f);

	w.shapes.push_back(&s);

	float root2 = sqrtf(2.0f);
	Ray r(point(0, 0, -3), vector(0, -root2 / 2.0f, root2 / 2.0f));
	Intersections xs{ Intersection(root2, &p) };

	Precomputation comp(xs[0], r, xs);
	Color c = w.shadeHit(comp, 5);

	EXPECT_EQ(c, Color(0.93642f, 0.68642f, 0.68642f));
}


TEST(RefractionTests, SchlickTest) {

	float root2 = sqrtf(2.0f);

	Sphere s = glassSphere();

	Ray r1(
		point(0, 0, root2 / 2.0f),
		vector(0, 1, 0)
	);

	Intersections xs1 =
	{
		Intersection{-root2/2.0f, &s},
		Intersection{root2/2.0f, &s}
	};

	Precomputation p1(xs1[1], r1, xs1);
	float reflectance1 = p1.schlick();

	EXPECT_EQ(reflectance1, 1.0f);


	Ray r2(
		point(0, 0, 0),
		vector(0, 1, 0)
	);

	Intersections xs2 =
	{
		Intersection{-1, &s},
		Intersection{1, &s}
	};

	Precomputation p2(xs2[1], r2, xs2);
	float reflectance2 = p2.schlick();

	EXPECT_TRUE(compareFloats(reflectance2, 0.04f));


	Ray r3(
		point(0, 0.99f, -2.0f),
		vector(0, 0, 1)
	);

	Intersections xs3 =
	{
		Intersection{1.8589f, &s}
	};

	Precomputation p3(xs3[0], r3, xs3);
	float reflectance3 = p3.schlick();

	EXPECT_TRUE(compareFloats(reflectance3, 0.48873f));


}


TEST(ReflectionRefractionTests, SchlickInShadeHit) {

	float root2 = sqrtf(2.0f);

	World w = testWorld();
	w.shapes.clear();

	Ray r(
		point(0, 0, -3),
		vector(0, -root2 / 2.0f, root2 / 2.0f)
	);

	Plane p;
	p.transform =
		Mat4(1.0f).translate(0, -1, 0);
	p.material.reflective = 0.5f;
	p.material.transperancy = 0.5f;
	p.material.refractiveIndex = 1.5f;

	w.shapes.push_back(&p);

	Sphere s;
	s.transform = Mat4(1.0f).translate(0, -3.5f, -0.5f);
	s.material.color = Color(1, 0, 0);
	s.material.ambient = 0.5f;

	w.shapes.push_back(&s);

	Intersections xs{
		Intersection{root2, &p}
	};

	Precomputation comp(xs[0], r, xs);
	Color c = w.shadeHit(comp, 5);
	std::cout << c.r << " " << c.g << " " << c.b;
	//EXPECT_EQ(c, Color(0.93391f, 0.69643f, 0.69243f));
}