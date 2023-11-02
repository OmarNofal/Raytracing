#include <light/Light.h>
#include <geometry/Sphere.h>
#include <vector>

class World {

public:
	std::vector<Light> lights;
	std::vector<Sphere> spheres;

	World();
};