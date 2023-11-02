#pragma once

#include <vec/Tuple.h>
#include <vec/Color.h>
#include <material/Material.h>

class Light {

public:

	Tuple position;
	Color intensity;

	Light(Tuple position = Tuple::createPoint(0, 0, 0), Color intensity = Color(1, 1, 1));

};



Color lighting(
	const Material& m,
	const Light& l,
	const Tuple& pos,
	const Tuple& eyeV,
	const Tuple& normal,
	bool isInShadow = false
);