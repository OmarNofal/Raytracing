#include <scene/World.h>
#include <algorithm>


World::World() {}
std::vector<Intersection> World::intersectRay(const Ray& r) const
{

	std::vector<Intersection> result;

	for (const auto& obj : shapes) {
		auto intersections = obj->intersectRay(r);
		result.insert(result.end(), intersections.begin(), intersections.end());
	}

	std::sort(result.begin(), result.end());

	return result;
}

Color World::shadeHit(const Precomputation& p, int remaining) const
{
	Color finalColor{ 0, 0 ,0 };

	for (const auto& light : lights) {
		bool inShadow = isPointInShadow(p.overPoint, light);
		finalColor = finalColor + lighting(
			p.s->material,
			*p.s,
			light, p.overPoint, p.eyeV, p.normalV, inShadow);
	}

	auto reflected = reflectedColor(p, remaining);

	return finalColor + reflected;
}

Color World::colorAt(const Ray& r, int remaining) const
{

	const auto& intersections = intersectRay(r);

	auto hit = findHit(intersections);
	if (hit == intersections.end()) return Color(0, 0, 0);
	
	Precomputation p(*hit, r);


	return shadeHit(p, remaining);
}

Color World::reflectedColor(const Precomputation& p, int remaining) const
{
	if (compareFloats(p.s->material.reflective, 0.0f) || remaining < 1) {
		return Color::black();
	}
	Ray reflectedRay(p.overPoint, p.reflectv);
	Color c = colorAt(reflectedRay, remaining - 1);
	return c * p.s->material.reflective;
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

