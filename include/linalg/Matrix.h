#pragma once

#include <initializer_list>
#include <utils/FloatUtils.h>
#include <vec/Tuple.h>
#include <ostream>
#include <string>

class Matrix {

protected:
	mutable Matrix* cachedInverse = nullptr;

public:
	size_t numRows = 0;
	size_t numColumns = 0;

	float* data = nullptr; // row-major order

	Matrix(size_t numRows, size_t numColumns, float initFloat = 0.0f);
	~Matrix();

	/*
		Initializes matrix with the lists values.
	*/
	Matrix(size_t numRows, size_t numColumns, std::initializer_list<float>);

	float getValueAt(size_t row, size_t column) const;
	void setValue(size_t row, size_t column, float);

	bool operator==(const Matrix&) const;
	Matrix operator*(const Matrix&) const;
	Matrix(const Matrix& m);
	Matrix(Matrix&& m) noexcept;
	
	Matrix transpose() const;
	Matrix subMatrix(size_t row, size_t column) const;


	Matrix& operator=(const Matrix& m);

};

class Mat2 : public Matrix {

public:

	Mat2();
	Mat2(float diagonalValues);

	Mat2(std::initializer_list<float> values);

	float determinant() const;

	static Mat2 identity();
};

class Mat3 : public Matrix {

public:
	Mat3(float diagonalValues);
	Mat3();

	Mat3(std::initializer_list<float> values);

	float minor(size_t row, size_t column) const;
	float cofactor(size_t row, size_t column) const;

	float determinant() const;

	static Mat3 identity();

};

class Mat4 : public Matrix {


public:
	Mat4(float diagonalValues);
	Mat4();

	Mat4(std::initializer_list<float> values);

	static Mat4 identity();

	Mat4 operator*(const Mat4&) const;
	Tuple operator*(const Tuple&) const;

	float minor(size_t row, size_t column) const;

	float cofactor(size_t row, size_t column) const;

	float determinant() const;


	Mat4 inverse() const;

	Mat4 translate(float x = 0.0f, float y = 0.0f, float z = 0.0f) const;

	Mat4 scale(float x, float y, float z) const;

	Mat4 rotate(float radX, float radY, float radZ) const;
	Mat4 shear(float, float, float, float, float, float) const;
};


Mat4 viewMatrix(
	Tuple from,
	Tuple to,
	Tuple up
);


static std::ostream& operator<<(std::ostream& s, const Matrix& m) {

	s << std::endl;
	for (int r = 0; r < m.numRows; r++) {

		for (int c = 0; c < m.numColumns; c++) {

			s << std::to_string(m.getValueAt(r, c)) << "   ";

		}

		s << std::endl;
	}
	return s;
}