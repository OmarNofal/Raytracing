#include <ray/Ray.h>
#include <ray/Intersection.h>

Ray::Ray(const Tuple& origin , const Tuple& direction) noexcept : origin(origin), direction(direction) {}

Tuple Ray::positionAt(float t) const
{
	return origin + direction * t;
}

std::vector<Intersection> Ray::findIntersections(const Sphere& s) const
{
	auto sphereToRay = origin - Tuple::createPoint(0, 0, 0);

	auto a = direction.dot(direction);
	auto b = 2 * direction.dot(sphereToRay);
	auto c = sphereToRay.dot(sphereToRay) - 1.0f;

	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0.0f) return {};

	float sqrtD = sqrtf(discriminant);

	float t2 = (-b + sqrtD) / (2 * a);
	float t1 = (-b - sqrtD) / (2 * a);

	return { {t1, s}, {t2, s} };
}
