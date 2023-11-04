#include <geometry/Sphere.h>
#include <ray/Intersection.h>
#include <ray/Ray.h>

Sphere::Sphere(const Mat4& t): Shape(t)
{}

Sphere::Sphere(Mat4&& t): Shape(t) {}

Sphere::Sphere() {};

Tuple Sphere::localNormalAt(const Tuple& p) const {
	auto objectNormal = p - Tuple::createPoint(0, 0, 0);
	return objectNormal;
}

bool Sphere::operator==(const Sphere& s) const
{
	return transform == transform;
}

Intersections Sphere::localIntersect(const Ray& localRay) const {
	auto& origin = localRay.origin;
	auto& direction = localRay.direction;

	auto sphereToRay = origin - Tuple::createPoint(0, 0, 0);

	auto a = direction.dot(direction);
	auto b = 2 * direction.dot(sphereToRay);
	auto c = sphereToRay.dot(sphereToRay) - 1.0f;

	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0.0f) return {};

	float sqrtD = sqrtf(discriminant);

	float t2 = (-b + sqrtD) / (2 * a);
	float t1 = (-b - sqrtD) / (2 * a);

	return { {t1, this}, {t2, this} };
}

