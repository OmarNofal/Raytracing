#pragma once

#include <vec/Color.h>

class Material {


public:
	float ambient = 0.1f;
	float diffuse = 0.9f;
	float specular = 0.9f;
	float shininess = 200.0f;
	Color color = Color(1, 1, 1);

	bool operator==(const Material& m) const;

};