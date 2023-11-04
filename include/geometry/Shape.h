#pragma once
#include <linalg/Matrix.h>
#include <material/Material.h>
#include <vector>

class Intersection;
class Ray;

class Shape {

protected:

	Shape(const Mat4& m);
	Shape(Mat4&& m);
	Shape();

private:
	virtual std::vector<Intersection> localIntersect(const Ray& r) const = 0;
	virtual Tuple localNormalAt(const Tuple& t) const = 0;

public:
	Mat4 transform = Mat4(1.0f);
	Material material;

	Tuple normalAt(const Tuple& t) const;
	
	std::vector<Intersection> intersectRay(const Ray& r) const;
};
