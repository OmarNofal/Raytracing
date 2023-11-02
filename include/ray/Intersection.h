#pragma once

#include <geometry/Sphere.h>
#include <vector>

class Intersection {

public:

	float t = 0.0f;
	Sphere s;

	Intersection(float t, Sphere s);

	Intersection& operator=(const Intersection&) = default;

	bool operator<(const Intersection&) const;

};




std::vector<Intersection>::const_iterator findHit(const std::vector<Intersection>& v);