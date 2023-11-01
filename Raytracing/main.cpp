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

int main() {

	Sphere s(Mat4::identity().scale(1.0f, 0.2f, 1.0f).rotate(0, 0, M_PI / 8.0f));

	Canvas c(256, 256);

	Tuple origin = Tuple::createPoint(0, 0, -5.0f);

	for (int i = 0; i < c.width; i++) {

		for (int j = 0; j < c.height; j++) {

			float pixelZ = 0.0f;
			float pixelX = (i / (c.width / 2.0f)) - 1.0f;
			float pixelY = -(j / (c.height / 2.0f)) + 1.0f;

			auto originToPx = Tuple::createPoint(pixelX, pixelY, pixelZ) - origin;

			Ray r(origin, originToPx.normalized());

			auto intersections = r.findIntersections(s);

			auto hit = findHit(intersections);
			if (hit != intersections.end()) {
				c.setColorAt(j, i, Color(1.0f));
			}
		}

	}

	SaveCanvas("First Sphere.jpg", c);

	ShellExecute(0, 0, L"First Sphere.jpg", 0, 0, SW_SHOW);
}