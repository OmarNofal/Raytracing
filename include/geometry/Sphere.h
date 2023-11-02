#pragma once
#include <linalg/Matrix.h>
#include <material/Material.h>

class Sphere {


public:

	Mat4 transform = Mat4::identity();
	Material material;

	Sphere(const Mat4& t);
	Sphere(Mat4&& t);
	Sphere();

	Tuple normalAt(const Tuple& p) const;

};