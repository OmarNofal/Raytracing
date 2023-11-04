#pragma once
#include <geometry/Shape.h>
#include <ray/Intersection.h>
#include <ray/Ray.h>

class Plane : public Shape {

private:
	Tuple localNormalAt(const Tuple& t) const override;
	Intersections localIntersect(const Ray& r) const override;

};