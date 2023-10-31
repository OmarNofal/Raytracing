#pragma once

#include <geometry/Sphere.h>
#include <vector>

class Intersection {

public:

	float t = 0.0f;
	const Sphere& s;

	Intersection(float t, const Sphere&);
};


std::vector<Intersection>::const_iterator findHit(const std::vector<Intersection>& v);