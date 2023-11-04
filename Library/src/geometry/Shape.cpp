#include <geometry/Shape.h>
#include <ray/Intersection.h>
#include <ray/Ray.h>

Shape::Shape() {};
Shape::Shape(const Mat4& m) : transform(m) {}
Shape::Shape(Mat4&& m) : transform(m) {}

Intersections Shape::intersectRay(const Ray& r) const {
	Ray localRay = r.transform(transform.inverse());
	return localIntersect(localRay);
}

Tuple Shape::normalAt(const Tuple& t) const {
	auto inversedTuple = transform.inverse() * t;
	auto localNormal = localNormalAt(inversedTuple);

	auto transformedNormal = *static_cast<Mat4*>(& transform.inverse().transpose()) * localNormal;
	transformedNormal.w = 0;

	return transformedNormal.normalized();
}