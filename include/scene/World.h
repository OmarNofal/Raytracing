#include <light/Light.h>
#include <geometry/Shape.h>
#include <vector>
#include <ray/Intersection.h>
#include <ray/Ray.h>
#include <ray/Precomputation.h>


#define DEFAULT_NUM_BOUNCES 4

class World {

public:
	std::vector<Light> lights;
	std::vector<Shape*> shapes;

	World();

	std::vector<Intersection> intersectRay(const Ray& r) const;

	Color shadeHit(const Precomputation& p, int remaining = DEFAULT_NUM_BOUNCES) const;

	Color colorAt(const Ray& r, int remaining = DEFAULT_NUM_BOUNCES) const;
	Color reflectedColor(const Precomputation& p, int remaining = DEFAULT_NUM_BOUNCES) const;
	Color refractedColor(const Precomputation& p, int remaining = DEFAULT_NUM_BOUNCES) const;

	bool isPointInShadow(const Tuple& p, const Light& l) const;

};