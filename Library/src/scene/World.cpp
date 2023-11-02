#include <scene/World.h>
#include <algorithm>


World::World() {}
std::vector<Intersection> World::intersectRay(const Ray& r) const
{

	std::vector<Intersection> result;

	for (auto& obj : spheres) {
		auto intersections = r.findIntersections(obj);
		result.insert(result.end(), intersections.begin(), intersections.end());
	}

	std::sort(result.begin(), result.end());

	return result;
}

Color World::shadeHit(const Precomputation& p) const
{
	Color finalColor{ 0, 0 ,0 };

	for (const auto& light : lights) {
		bool inShadow = isPointInShadow(p.overPoint, light);
		finalColor = finalColor + lighting(
			p.s.material,
			light, p.overPoint, p.eyeV, p.normalV, inShadow);
	}

	return finalColor;
}

Color World::colorAt(const Ray& r) const
{

	const auto& intersections = intersectRay(r);

	auto hit = findHit(intersections);
	if (hit == intersections.end()) return Color(0, 0, 0);
	
	Precomputation p(*hit, r);


	return shadeHit(p);
}

bool World::isPointInShadow(const Tuple& p, const Light& l) const
{

	auto v = l.position - p;
	auto distance = v.magnitude();
	auto direction = v.normalized();

	Ray r(p, direction);
	auto intersections = intersectRay(r);

	auto hit = findHit(intersections);
	if (hit != intersections.end()) {
		if (hit->t < distance) return true;
	}

	return false;
}

