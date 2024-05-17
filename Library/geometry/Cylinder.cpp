#include <geometry/Cylinder.h>

Tuple Cylinder::localNormalAt(const Tuple& t) const
{

	float dist = t.x * t.x + t.z * t.z;
	if (dist < 1 && t.y >= maximum - EPSILON) {
		return vector(0, 1, 0);
	}
	else if (dist < 1 && t.y <= minimum + EPSILON) {
		return vector(0, -1, 0);
	}

	return vector(t.x, 0, t.z);
}

Intersections Cylinder::localIntersect(const Ray& r) const
{

	float a = r.direction.x * r.direction.x + r.direction.z * r.direction.z;
	if (compareFloats(a, 0.0f)) {
		Intersections xs;
		intersectCaps(r, xs);
		return xs;
	}

	float b = 2 * r.origin.x * r.direction.x + 2 * r.origin.z * r.direction.z;
	float c = r.origin.x * r.origin.x + r.origin.z * r.origin.z - 1;

	float disc = b * b - 4 * a * c;

	if (disc < 0) {
		Intersections xs;
		intersectCaps(r, xs);
		return xs;
	}

	float t0 = (-b - sqrtf(disc)) / (2 * a);
	float t1 = (-b + sqrtf(disc)) / (2 * a);

	if (t0 > t1) std::swap(t0, t1);

	Intersections xs;

	float y1 = r.positionAt(t0).y;
	if (y1 > minimum && y1 < maximum) {
		xs.push_back(Intersection{ t0, this });
	}


	float y2 = r.positionAt(t1).y;
	if (y2 > minimum && y2 < maximum) {
		xs.push_back(Intersection{ t1, this });
	}

	intersectCaps(r, xs);

	return xs;
}


bool Cylinder::checkCapIntersection(const Ray& r, float t) const {

	float x = r.positionAt(t).x;
	float z = r.positionAt(t).z;

	return (x * x + z * z) <= 1.0f;
}


void Cylinder::intersectCaps(const Ray& r, Intersections& xs) const {

	if (!closed || compareFloats(r.direction.y, 0.0f)) {
		return;
	}

	float t = (minimum - r.origin.y) / r.direction.y;
	if (checkCapIntersection(r, t)) {
		xs.push_back({ t, this });
	}

	t = (maximum - r.origin.y) / r.direction.y;
	if (checkCapIntersection(r, t)) {
		xs.push_back({ t, this });
	}
}