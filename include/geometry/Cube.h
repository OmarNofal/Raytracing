#pragma once
#include <geometry/Shape.h>
#include <ray/Intersection.h>
#include <ray/Ray.h>

class Cube : public Shape {

private:
	Tuple localNormalAt(const Tuple& t) const override;
	Intersections localIntersect(const Ray& r) const override;

	std::tuple<float, float> checkAxis(float origin, float direction) const;

};