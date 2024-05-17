#include <geometry/Cube.h>
#include <utils/FloatUtils.h>
#include <limits>
#include <tuple>

Tuple Cube::localNormalAt(const Tuple& t) const
{
	auto maxC = std::max(std::max(abs(t.x), abs(t.y)), abs(t.z));

	if (maxC == abs(t.x)) {
		return vector(t.x, 0, 0);
	}
	else if (maxC == abs(t.y)) {
		return vector(0, t.y, 0);
	}
	else {
		return vector(0, 0, t.z);
	}
}

Intersections Cube::localIntersect(const Ray& r) const
{

	auto xIntersections = checkAxis(r.origin.x, r.direction.x);
	auto yIntersections = checkAxis(r.origin.y, r.direction.y);
	auto zIntersections = checkAxis(r.origin.z, r.direction.z);

	float xtMin = std::get<0>(xIntersections), xtMax = std::get<1>(xIntersections);
	float ytMin = std::get<0>(yIntersections), ytMax = std::get<1>(yIntersections);
	float ztMin = std::get<0>(zIntersections), ztMax = std::get<1>(zIntersections);

	float tMin = std::max(xtMin, std::max(ytMin, ztMin));
	float tMax = std::min(xtMax, std::min(ytMax, ztMax));

	if (tMin > tMax) return {};
	
	return Intersections{
		{tMin, this},
		{tMax, this}
	};
}

std::tuple<float, float> Cube::checkAxis(float origin, float direction) const
{

	float tMinNumerator = -1 - origin;
	float tMaxNumerator = 1 - origin;

	float tMin, tMax;

	if (abs(direction) >= 0.0001f) {
		tMin = tMinNumerator / direction;
		tMax = tMaxNumerator / direction;
	} else {
		auto infinity =
			std::numeric_limits<float>::infinity();
		tMin = tMinNumerator * infinity;
		tMax = tMaxNumerator * infinity;
	}

	if (tMin > tMax) {
		std::swap(tMin, tMax);
	}

	return std::tuple<float, float>(tMin, tMax);
}
