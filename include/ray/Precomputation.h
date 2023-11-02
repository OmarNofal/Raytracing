#pragma once

#include <ray/Ray.h>

constexpr float EPSILON = 0.01f;

class Precomputation {

public:
	float t;
	Sphere s;
	Tuple point;
	Tuple eyeV;
	Tuple normalV;
	Tuple overPoint;
	bool inside;


	Precomputation(const Intersection& i, const Ray& r);

}; 