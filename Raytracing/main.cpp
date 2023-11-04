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

int main() {

	Sphere middle;
	middle.transform = Mat4(1.0f)
		.translate(-0.5, 1.0, 0.5);
	middle.material.color = Color(0.1, 1, 0.5);
	middle.material.diffuse = 0.7f;
	middle.material.specular = 0.3f;

	Sphere smallSphere;
	smallSphere.transform = Mat4(1.0f)
		.scale(0.5, 0.5, 0.5)
		.translate(1.5f, 0.5f, -0.5f);
	smallSphere.material.color = Color(0.5, 1, 0.1);
	smallSphere.material.diffuse = 0.7f;
	smallSphere.material.specular = 0.3f;


	Light l(Tuple::createPoint(-10, 10, -10));

	Camera c(4000, 4000, M_PI / 3.0f);
	c.transform = viewMatrix(
		point(0, 1.5, -5),
		point(0, 1, 0),
		vector(0, 1, 0)
	);


	Plane floor;
	floor.material.color = Color(0.2f, 0.6f, 0.2f);

	Plane backWall;
	backWall.material.color = Color(0.4f, 0.2f, 0.4f);
	backWall.transform = Mat4(1.0f).rotate(M_PI / 2.0f, 0, 0).translate(0, 0, 10.0f);
	backWall.material.specular = 0.0f;

	World w;
	//w.shapes.push_back(&floor);
	w.shapes.push_back(&backWall);
	w.shapes.push_back(&smallSphere);
	w.shapes.push_back(&middle);
	w.shapes.push_back(&floor);

	w.lights.push_back(l);

	SaveCanvas("First Sphere.jpg", c.render(w, true));

	ShellExecute(0, 0, L"First Sphere.jpg", 0, 0, SW_SHOW);
}