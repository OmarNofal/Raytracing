#include <material/Material.h>
#include <utils/FloatUtils.h>

void Material::setPattern(Pattern *p)
{
	pattern.reset(p);
}

Material& Material::operator=(const Material& m)
{
	ambient = m.ambient;
	diffuse = m.diffuse;
	specular = m.specular;
	shininess = m.shininess;
	color = m.color;
	pattern.reset(m.pattern.get());
	return *this;
}

bool Material::operator==(const Material& m) const {
	return compareFloats(ambient, m.ambient) &&
		compareFloats(diffuse, m.diffuse) &&
		compareFloats(specular, m.specular) &&
		compareFloats(shininess, m.shininess) &&
		m.pattern == pattern;
}