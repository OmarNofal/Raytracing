#include <light/Light.h>
#include <geometry/Shape.h>
#include <vector>
#include <ray/Intersection.h>
#include <ray/Ray.h>
#include <ray/Precomputation.h>

class World {

public:
	std::vector<Light> lights;
	std::vector<Shape*> shapes;

	World();

	std::vector<Intersection> intersectRay(const Ray& r) const;

	Color shadeHit(const Precomputation& p) const;

	Color colorAt(const Ray& r) const;

	bool isPointInShadow(const Tuple& p, const Light& l) const;

};