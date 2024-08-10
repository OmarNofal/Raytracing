#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <cmath>
#include <linalg/Matrix.h>
#include <iostream>
#include <canvas/Canvas.h>
#include <canvas/CanvasSaver.h>
#include <geometry/Sphere.h>
#include <ray/Ray.h>
#include <Windows.h>
#include <ray/Intersection.h>
#include <material/Material.h>
#include <light/Light.h>
#include <camera/Camera.h>
#include <geometry/Plane.h>
#include <geometry/Cube.h>
#include <geometry/Cylinder.h>
#include <geometry/Cone.h>

int main() {



	Camera c(1000, 1000, M_PI / 2);
	c.transform = viewMatrix(
		point(-1, 0, 8),
		point(1, 0, 0),
		vector(0, 1, 0)
	);


	Cube room;
	room.transform = Mat4(1.0f).scale(10.0f, 10.0f, 10.0f);
	room.material.pattern.reset(new CheckerPattern(Color::white(), Color::black()));
	room.material.specular = 0.0f;
	room.material.pattern->transform = Mat4(1.0f).scale(0.25, 0.25, 0.25);


	Cube mirror;
	mirror.transform = Mat4(1.0f).scale(0.5f, 3.0f, 5.0f).translate(10.49f, 0, 0);
	mirror.material.specular = 0.3f;

	mirror.material.reflective = 0.7f;
	mirror.material.color = Color(0.5f, 0.3f, 0.3f);
	mirror.material.diffuse = 0.2f;

	Cone cyl;

	cyl.maximum = 0;
	cyl.minimum = -1.06f;
	cyl.transform = Mat4(1.0f).rotate(-M_PI / 2.0f, 0, -M_PI / 3.0f).translate(4.0f, 0, 0);
	cyl.material.ambient = 0.2f;
	cyl.material.color = Color(0.3f, 0.5f, 0.3f);
	cyl.material.pattern.reset(new StripePattern({ 0, 0, 0 }, { 1,1,1 }));
	cyl.material.pattern->transform = Mat4(1.0).scale(0.25, 0.25, 0.25);
	cyl.closed = true;

	World w;
	w.shapes.push_back(&room);
	w.shapes.push_back(&mirror);
	w.shapes.push_back(&cyl);

	Light l;
	l.position = point(0, 2, 0);

	w.lights.push_back(l);

	

	SaveCanvas("out.jpg", c.render(w, true));
	ShellExecute(0, 0, L"out.jpg", 0, 0, SW_SHOW);
}