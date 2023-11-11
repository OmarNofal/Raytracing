#pragma once

#include <ray/Ray.h>

constexpr float EPSILON = 0.005f;

class Precomputation {

public:
	float t;
	const Shape* s;
	Tuple point;
	Tuple eyeV;
	Tuple normalV;
	Tuple overPoint;
	Tuple reflectv;
	bool inside;

	
	Precomputation(const Intersection& i, const Ray& r);

}; 