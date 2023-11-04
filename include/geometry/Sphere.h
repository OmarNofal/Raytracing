#pragma once
#include <linalg/Matrix.h>
#include <material/Material.h>
#include <geometry/Shape.h>

class Sphere : public Shape {


private:
	std::vector<Intersection> localIntersect(const Ray& localRay) const override;
	Tuple localNormalAt(const Tuple& localPoint) const override;

public:

	Sphere(const Mat4& t);
	Sphere(Mat4&& t);
	Sphere();

	bool operator==(const Sphere& s) const;
};