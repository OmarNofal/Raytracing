
#include <light/Light.h>
#include <cmath>
#include <geometry/Shape.h>

Light::Light(Tuple position, Color intensity): position(position), intensity(intensity)
{
}



Color lighting(
	const Material& m,
	const Shape& s,
	const Light& l,
	const Tuple& pos,
	const Tuple& eyeV,
	const Tuple& normal,
	bool isInShadow
) {
	Color color = m.color;
	if (m.pattern.get() != nullptr) {
		color = m.pattern->getColorAtObject(s, pos);
	}

	auto effectiveColor = l.intensity * color;
	auto ambient = effectiveColor * m.ambient;
	if (isInShadow) return ambient;

	auto lightV = (l.position - pos).normalized();
	auto lightDotNormal = lightV.dot(normal);

	auto diffuse = Color(0, 0, 0);
	auto specular = Color(0, 0, 0);

	if (lightDotNormal > 0) {
		diffuse = lightDotNormal * m.diffuse * effectiveColor;
	
		auto reflectedLight = (-1.0f * lightV).reflect(normal).normalized();

		auto reflectionStrength = reflectedLight.dot(eyeV);
		if (reflectionStrength > 0) {
			auto factor = powf(reflectionStrength, m.shininess);
			specular = factor * m.specular * l.intensity;
		}
	
	}

	return ambient + diffuse + specular;
}