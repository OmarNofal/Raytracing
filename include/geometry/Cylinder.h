#pragma once
#include <geometry/Shape.h>
#include <ray/Intersection.h>
#include <ray/Ray.h>
#include <limits>

class Cylinder : public Shape {

public:
	float minimum = -std::numeric_limits<float>::infinity();
	float maximum = std::numeric_limits<float>::infinity();

	float closed = false;

private:
	Tuple localNormalAt(const Tuple& t) const override;
	Intersections localIntersect(const Ray& r) const override;
	bool checkCapIntersection(const Ray& r, float t) const;
	void intersectCaps(const Ray& r, Intersections& xs) const;
};