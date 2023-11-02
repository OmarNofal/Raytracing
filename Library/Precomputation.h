#pragma once

#include <ray/Ray.h>

class Precomputation {

public:
	float t;
	Sphere s;
	Tuple point;
	Tuple eyeV;
	Tuple normalV;


	Precomputation(const Intersection& i, const Ray& r);

};