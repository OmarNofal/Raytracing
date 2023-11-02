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

int main() {

	Sphere floor;
	floor.transform = Mat4(1.0f).scale(10 ,0.01, 10);
	floor.material.color = Color(1, 0.9, 0.9);
	floor.material.specular = 0;

	Sphere leftWall;
	leftWall.transform = Mat4(1.0f)
		.scale(10, 0.01, 10)
		.rotate(M_PI / 2.0f, -M_PI / 4.0f, 0)
		.translate(0, 0, 5);
	leftWall.material = floor.material;

	Sphere rightWall;
	rightWall.transform = Mat4(1.0f)
		.scale(10, 0.01, 10)
		.rotate(M_PI / 2.0f, M_PI / 4.0f, 0)
		.translate(0, 0, 5);
	rightWall.material = floor.material;


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

	Camera c(3000, 3000, M_PI / 3.0f);
	c.transform = viewMatrix(
		Tuple::createPoint(0, 1.5, -5),
		Tuple::createPoint(0, 1, 0),
		Tuple::createVector(0, 1, 0)
	);

	World w;
	w.spheres.push_back(floor);
	w.spheres.push_back(leftWall);
	w.spheres.push_back(rightWall);
	w.spheres.push_back(smallSphere);
	w.spheres.push_back(middle);

	w.lights.push_back(l);

	SaveCanvas("First Sphere.jpg", c.render(w, true));

	ShellExecute(0, 0, L"First Sphere.jpg", 0, 0, SW_SHOW);
}