#include <light/Light.h>

#include <gtest/gtest.h>
#include <material/Material.h>

TEST(LightTests, LightInit) {

	Light l;

	EXPECT_EQ(l.position, Tuple::createPoint(0, 0, 0));
	EXPECT_EQ(l.intensity, Color(1, 1, 1));


}



TEST(LightTests, LightingFunction) {


	Material m;

	auto p = Tuple::createPoint(0, 0, 0);

	Light l1(Tuple::createPoint(0, 0, -10));
	Tuple nV = Tuple::createVector(0, 0, -1);
	Tuple eyeV = Tuple::createPoint(0, 0, -1);

	EXPECT_EQ(lighting(m, l1, p, eyeV, nV), Color(1.9f, 1.9f, 1.9f) );


	Tuple eye2 = Tuple::createVector(0, sqrtf(2) / 2, -sqrtf(2) / 2);
	EXPECT_EQ(lighting(m, l1, p, eye2, nV), Color(1.0f, 1.0f, 1.0f));
	EXPECT_EQ(lighting(m, l1, p, eye2, nV, true), Color(0.1f, 0.1f, 0.1f));

	Light l2(Tuple::createPoint(0, 10, -10));

	EXPECT_EQ(lighting(m, l2, p, eyeV, nV), Color(0.7364f, 0.7364f, 0.7364f));


	Tuple eye3 = Tuple::createVector(0, -sqrtf(2) / 2, -sqrtf(2) / 2);
	EXPECT_EQ(lighting(m, l2, p, eye3, nV), Color(1.6364f, 1.6364f, 1.6364f));

	Light l3(Tuple::createPoint(0, 0, 10));

	EXPECT_EQ(lighting(m, l3, p, eyeV, nV), Color(0.1, 0.1, 0.1));


}