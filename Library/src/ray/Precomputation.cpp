#include <ray/Precomputation.h>


Precomputation::Precomputation(const Intersection& i, const Ray& r): s(i.s), t(i.t) {

	point = r.positionAt(t);
	eyeV = -r.direction;
	normalV = s->normalAt(point);

	if (eyeV.dot(normalV) < 0) {
		inside = true;
		normalV = -normalV;
	}
	else {
		inside = false;
	}

	overPoint = point + EPSILON * normalV ;
}
