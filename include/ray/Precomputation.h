#pragma once

#include <ray/Ray.h>

class Precomputation {

public:
	float t;
	const Shape* s;
	Tuple point;
	Tuple eyeV;
	Tuple normalV;
	Tuple overPoint;
	Tuple underPoint;
	Tuple reflectv;
	bool inside;
	float n1;
	float n2;

	
	Precomputation(
		const Intersection& i,
		const Ray& r,
		const Intersections& xs = Intersections()
	);

	float schlick() const;
}; 