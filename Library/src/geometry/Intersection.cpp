#include <ray/Intersection.h>




Intersection::Intersection(float t, const Sphere& s) : s(s), t(t) {};


std::vector<Intersection>::const_iterator findHit(const std::vector<Intersection>& v) {
	auto it = v.end();
	float minT = std::numeric_limits<float>::max();

	for (auto b = v.begin(); b < v.end(); b++) {
		if (b->t >= 0.0f && b->t < minT) {
			minT = b->t;
			it = b;
		}
	}

	return it;
}