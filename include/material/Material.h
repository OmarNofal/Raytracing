#pragma once

#include <memory>
#include <vec/Color.h>
#include "Pattern.h"

class Material {


public:
	float ambient = 0.1f;
	float diffuse = 0.9f;
	float specular = 0.9f;
	float shininess = 200.0f;
	float reflective = 0.0f;
	float transperancy = 0.0f;
	float refractiveIndex = 1.0f;

	Color color = Color(1, 1, 1);
	std::unique_ptr<Pattern> pattern;

	void setPattern(Pattern* p);

	Material& operator=(const Material& m);

	bool operator==(const Material& m) const;

};