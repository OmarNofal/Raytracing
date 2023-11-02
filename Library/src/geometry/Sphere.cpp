#include <geometry/Sphere.h>


Sphere::Sphere(const Mat4& t): transform(t)
{}

Sphere::Sphere(Mat4&& t): transform(t){}

Sphere::Sphere() {};

Tuple Sphere::normalAt(const Tuple& p) const {

	auto inverseTransform = transform.inverse();

	auto objectPoint = inverseTransform * p;
	auto objectNormal = objectPoint - Tuple::createPoint(0, 0, 0);

	auto worldNormal = *static_cast<Mat4*>(&inverseTransform.transpose()) * objectNormal;
	worldNormal.w = 0;

	return worldNormal.normalized();
}

bool Sphere::operator==(const Sphere& s) const
{
	return transform == transform;
}
