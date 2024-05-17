#pragma once

#include <geometry/Shape.h>
#include <vector>

class Intersection {

public:

	float t = 0.0f;
	const Shape* s;

	Intersection(float t, const Shape* s) noexcept;

	bool operator==(const Intersection&) const;
	bool operator<(const Intersection&) const;

};

using Intersections = std::vector<Intersection>;


std::vector<Intersection>::const_iterator findHit(const std::vector<Intersection>& v);