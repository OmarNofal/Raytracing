#pragma once
#include <linalg/Matrix.h>

class Sphere {


public:

	Mat4 transform = Mat4::identity();

	Sphere(const Mat4& t);
	Sphere(Mat4&& t);
	Sphere();

};