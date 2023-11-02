#pragma once
#include <linalg/Matrix.h>
#include <ray/Ray.h>
#include <canvas/Canvas.h>
#include <scene/World.h>

class Camera {

public:
	size_t hSize;
	size_t vSize;
	float fov;
	Mat4 transform;

	float halfWidth;
	float halfHeight;

	float pixelSize = 0.0f;

	Camera(size_t hSize, size_t vSize, float fov, Mat4 transform = Mat4(1.0f));

	Ray rayForPixel(size_t x, size_t y) const;
	Canvas render(const World& w, bool verbose = false) const;
};