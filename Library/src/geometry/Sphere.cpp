#include <geometry/Sphere.h>


Sphere::Sphere(const Mat4& t): transform(t)
{}

Sphere::Sphere(Mat4&& t): transform(t){}

Sphere::Sphere() {};