#include <geometry/Cone.h>



Tuple Cone::localNormalAt(const Tuple& t) const
{
	float dist = sqrtf(t.x * t.x + t.z * t.z);
	if (dist < maximum  && t.y >= maximum - EPSILON) {
		return vector(0, 1, 0);
	}
	else if (dist < minimum && t.y <= minimum + EPSILON) {
		return vector(0, -1, 0);
	}

	float y = sqrtf(t.x * t.x + t.z * t.z);
	if (t.y > 0) y = -y;

	return vector(t.x, y, t.z);
}


Intersections Cone::localIntersect(const Ray& r) const
{
	
	auto& rO = r.origin;
	auto& rD = r.direction;

	float a = rD.x * rD.x - rD.y * rD.y + rD.z * rD.z;
	float b = 2 * rO.x * rD.x - 2 * rO.y * rD.y + 2 * rO.z * rD.z;
	float c = rO.x * rO.x - rO.y * rO.y + rO.z * rO.z;
	
	if (compareFloats(a, 0.0f)) {
		
		if (compareFloats(b, 0.0f)) {
			// no intersections
			return {};
		}

		float t = -c / (2 * b);

		Intersections xs;
		
		float y0 = r.positionAt(t).y;
		if (y0 >= minimum && y0 <= maximum)
			xs.push_back({ t, this });

		return xs;
	}
	else {

		float disc = b * b - 4 * a * c;

		if (disc < 0) return {};

		float t0 = (-b - std::sqrtf(disc)) / (2 * a);
		float t1 = (-b + std::sqrtf(disc)) / (2 * a);

		if (t0 > t1) std::swap(t0, t1);

		Intersections xs;

		float y0 = r.positionAt(t0).y;
		if (y0 >= minimum && y0 <= maximum)
			xs.push_back({ t0, this });

		float y1 = r.positionAt(t1).y;
		if (y1 >= minimum && y1 <= maximum)
			xs.push_back({ t1, this });

		intersectCaps(r, xs);

		return xs;
	}

}


bool Cone::checkCapIntersection(const Ray& r, float t, float radius) const
{
    
	float x = r.positionAt(t).x;
	float z = r.positionAt(t).z;

	return (x * x + z * z) <= radius * radius;
}


void Cone::intersectCaps(const Ray& r, Intersections& xs) const
{

	if (!closed || compareFloats(r.direction.y, 0.0f)) {
		return;
	}

	float t = (minimum - r.origin.y) / r.direction.y;
	if (checkCapIntersection(r, t, minimum)) {
		xs.push_back({ t, this });
	}

	t = (maximum - r.origin.y) / r.direction.y;
	if (checkCapIntersection(r, t, maximum)) {
		xs.push_back({ t, this });
	}

}
