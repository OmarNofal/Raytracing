#include <material/Material.h>
#include <utils/FloatUtils.h>

bool Material::operator==(const Material& m) const {
	return compareFloats(ambient, m.ambient) &&
		compareFloats(diffuse, m.diffuse) &&
		compareFloats(specular, m.specular) &&
		compareFloats(shininess, m.shininess);
}