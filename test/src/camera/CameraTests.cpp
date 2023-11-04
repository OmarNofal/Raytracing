#include <camera/Camera.h>
#include <gtest/gtest.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <canvas/Canvas.h>

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



TEST(CameraTests, CameraInit) {
	Camera c(
		120,
		250,
		((float) M_PI) / 4.0f
	);

	EXPECT_EQ(c.hSize, 120);
	EXPECT_EQ(c.vSize, 250);
	EXPECT_EQ(c.fov, ( (float) M_PI) / 4.0f);

}


TEST(CameraTests, PixelSizeCalculation) {

	Camera c1(200, 125, M_PI / 2);
	EXPECT_EQ(c1.pixelSize, 0.01f);

	Camera c2(125, 200, M_PI / 2);
	EXPECT_EQ(c2.pixelSize, 0.01f);

}

TEST(CameraTests, CameraRays) {

	Camera c1(201, 101, (float)M_PI / 2.0f);
	auto r1 = c1.rayForPixel(100, 50);

	EXPECT_EQ(r1.origin, Tuple::createPoint(0, 0, 0));
	EXPECT_EQ(r1.direction, Tuple::createVector(0, 0, -1));


	auto r2 = c1.rayForPixel(0, 0);
	EXPECT_EQ(r2.origin, Tuple::createPoint(0, 0, 0));
	EXPECT_EQ(r2.direction, Tuple::createVector(0.66519, 0.33259, -0.66851));

	c1.transform = Mat4(1.0f).translate(0, -2, 5)
		.rotate(0, M_PI / 4.0f, 0);

	auto r3 = c1.rayForPixel(100, 50);
	EXPECT_EQ(r3.origin, Tuple::createPoint(0, 2, -5));
	EXPECT_EQ(r3.direction, Tuple::createVector(sqrtf(2) / 2.0f, 0, -sqrtf(2) / 2.0f));


}


TEST(CameraTests, Render) {

	World w = testWorld();
	Camera c(11, 11, M_PI / 2.0f);

	auto from = Tuple::createPoint(0, 0, -5);
	auto to = Tuple::createPoint(0, 0, 0);
	auto up = Tuple::createVector(0, 1, 0);

	c.transform = viewMatrix(from, to, up);

	Canvas image = c.render(w);
	EXPECT_EQ(image.getColorAt(5, 5), Color(0.38066f, 0.47583f, 0.2855f));

}
