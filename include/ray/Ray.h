#pragma once

#include <vector>
#include <vec/Tuple.h>
#include <geometry/Sphere.h>
#include <ray/Intersection.h>
#include <linalg/Matrix.h>

class Ray {


public:
	Tuple origin;
	Tuple direction;

	Ray(const Tuple& origin = {0, 0, 0, 1}, const Tuple& direction = { 0, 0, 0, 0 }) noexcept;

	Tuple positionAt(float t) const;

	std::vector<Intersection> findIntersections(const Sphere& s) const;

	Ray transform(const Mat4& transform) const;

};