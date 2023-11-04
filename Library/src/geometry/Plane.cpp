#include <geometry/Plane.h>


Intersections Plane::localIntersect(const Ray& r) const {

	// if the ray is parallel to the plane
	if (compareFloats(r.direction.y, 0.0f)) {
		return {};
	}


	return { {-r.origin.y / r.direction.y, this} };
}


Tuple Plane::localNormalAt(const Tuple& t) const {
	return vector(0, 1, 0);
}