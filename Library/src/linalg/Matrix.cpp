#include <linalg/Matrix.h>
#include <algorithm>
#include <utils/FloatUtils.h>


Matrix::Matrix(size_t nRow, size_t nColumn, float initFloat): numRows(nRow), numColumns(nColumn) {


	data = new float[nRow * nColumn];

	for (int i = 0; i < nRow; i++) {
		for (int j = 0; j < nColumn; j++) {
			data[i * nColumn + j] = initFloat;
		}
	}

}

Matrix::Matrix(size_t numRows, size_t numColumns, std::initializer_list<float> values): Matrix(numRows, numColumns) {
	for (int i = 0; i < std::min<int>(numRows * numColumns, values.size()); i++) {
		data[i] = values.begin()[i];
	}
}


Matrix::~Matrix() {
	delete[] data;
}

bool Matrix::operator==(const Matrix& m) const {
	if (numRows != m.numRows || numColumns != m.numColumns) return false;
	
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numColumns; j++) {
			if (!compareFloats(getValueAt(i, j), m.getValueAt(i, j)))
				return false;
		}
	}
	return true;
}

Matrix Matrix::operator*(const Matrix& m) const
{
	if (numColumns != m.numRows) throw "MatrixMult: m1.nColumns != m2.nRows";

	Matrix resultMatrix(this->numRows, m.numColumns);
	
	for (int i = 0; i < numRows; i++) {
		
		float* rowStart = this->data + i*numColumns;
		

		for (int j = 0; j < m.numColumns; j++) {

			float* columnStart = m.data + j;

			float value = 0.0f;
			for (int z = 0; z < this->numColumns; z++) {
				value += rowStart[z] * columnStart[z * m.numColumns];
			}

			resultMatrix.setValue(i, j, value);
		}
	}

	return resultMatrix;
}

Matrix::Matrix(const Matrix& m)
{
	numRows = m.numRows;
	numColumns = m.numColumns;
	data = new float[numRows * numColumns];
	memcpy(data, m.data, numRows * numColumns * sizeof(float));
}

Matrix::Matrix(Matrix&& m) noexcept
{
	numColumns = m.numColumns;
	numRows = m.numRows;
	data = m.data;
	m.data = nullptr;
}

Matrix Matrix::transpose() const
{
	
	Matrix result(numColumns, numRows);

	for (int i = 0; i < numColumns; i++) {

		for (int j = 0; j < numRows; j++) {
			result.setValue(i, j, getValueAt(j, i));
		}

	}
	return result;
}

Tuple Mat4::operator*(const Tuple& t) const
{
	if (numColumns != 4) throw "MatrixMult: m1.nColumns != tupleSize(4)";
	
	Tuple result;

	for (int i = 0; i < numRows; i++) {

		float* rowStart = this->data + i * numColumns;

		float value = 0.0f;
		value = rowStart[0] * t.x
			+ rowStart[1] * t.y
			+ rowStart[2] * t.z
			+ rowStart[3] * t.w;

		switch (i) {
		case 0: 
			result.x = value;
			break;
		case 1:
			result.y = value;
			break;
		case 2:
			result.z = value;
			break;
		case 3:
			result.w = value;
			break;
		}
	}

	return result;
}

Matrix Matrix::subMatrix(size_t row, size_t column) const {

	Matrix m{ this->numRows - 1, this->numColumns - 1 };

	for (int i = 0; i < (numRows - 1); i++) {
		for (int j = 0; j < (numColumns - 1); j++) {

			size_t rowAddOne = (i >= row) ? 1 : 0;
			size_t colAddOne = (j >= column) ? 1 : 0;

			m.setValue(i, j, this->getValueAt(i + rowAddOne, j + colAddOne));
		}
	}
	return m;
}

Matrix& Matrix::operator=(const Matrix& m)
{
	if (data != nullptr)
		delete[] data;

	data = new float[m.numRows * m.numColumns];
	memcpy(data, m.data, m.numRows * m.numColumns * sizeof(float));
	numRows = m.numRows;
	numColumns = m.numColumns;

	return *this;
}


float Matrix::getValueAt(size_t r, size_t c) const {
	if (r >= numRows || r < 0 || c >= numColumns || c < 0) throw "OutOfBoundsException";
	return data[r * numColumns + c];
}

void Matrix::setValue(size_t r, size_t c, float value) {
	if (r >= numRows || r < 0 || c >= numColumns || c < 0) throw "OutOfBoundsException";
	data[r * numColumns + c] = value;
}




Mat2::Mat2(): Matrix(2, 2) {}
Mat2::Mat2(float diagonalValues): Matrix(2, 2) {
	data[0] = data[3]  = diagonalValues;
}
Mat2 Mat2::identity() { return Mat2(1.0f); }
Mat2::Mat2(std::initializer_list<float> values) : Matrix(2 , 2, values) {}
float Mat2::determinant() const {
	return data[0] * data[3] - data[2] * data[1];
}



Mat3::Mat3() : Matrix(3, 3) {}
Mat3::Mat3(float diagonalValues) : Matrix(3, 3) {
	data[0] = data[4] = data[8] = diagonalValues;
}
Mat3 Mat3::identity() {
	return Mat3(1.0f);
}
Mat3::Mat3(std::initializer_list<float> values) : Matrix(3, 3, values) {}

float Mat3::minor(size_t row, size_t column) const {

	Matrix sub = this->subMatrix(row, column);	
	Mat2& subMatrix = *static_cast<Mat2*>(&sub);
	
	return subMatrix.determinant();
}

float Mat3::cofactor(size_t row, size_t column) const {
	float m = minor(row, column);
	return (powf(-1.0f, row + column)) * m;
}

float Mat3::determinant() const {

	float det = 0;

	for (int i = 0; i < 3; i++)
		det += data[i] * cofactor(0, i);

	return det;
}


Mat4::Mat4() : Matrix(4, 4) {}
Mat4::Mat4(float diagonalValues) : Matrix(4, 4) {
	data[0] = data[5] = data[10] = data[15] = diagonalValues;
}
Mat4::Mat4(std::initializer_list<float> values): Matrix(4, 4, values) {}

Mat4 Mat4::identity() {
	return Mat4(1.0f);
}


float Mat4::minor(size_t row, size_t column) const {
	Matrix sub = this->subMatrix(row, column);
	Mat3& subMatrix = *static_cast<Mat3*>(&sub);

	return subMatrix.determinant();
}

float Mat4::cofactor(size_t row, size_t column) const {
	float m = minor(row, column);
	return (powf(-1.0f, row + column)) * m;
}


float Mat4::determinant() const {

	float det = 0;

	for (int i = 0; i < 4; i++)
		det += data[i] * cofactor(0, i);

	return det;
}

Mat4 Mat4::inverse() const
{

	float det = this->determinant();

	if (compareFloats(det, 0.0f)) {
		throw "Attempt to invert zero-determinant matrix";
	}

	Mat4 result;

	for (int i = 0; i < 4; i++) {

		for (int j = 0; j < 4; j++) {

			auto cofact = cofactor(i, j);
			
			result.setValue(j, i, cofact / det);
		}

	}


	return result;
}


Mat4 Mat4::operator*(const Mat4& m) const {
	Matrix result = ((Matrix) *this) * ((Matrix)m);
	Mat4& r1 = *(static_cast<Mat4*>(&result));
	return r1;
}

Mat4 Mat4::translate(float x, float y, float z) const {

	Mat4 translationMatrix(1.0f);
	translationMatrix.setValue(0, 3, x);
	translationMatrix.setValue(1, 3, y);
	translationMatrix.setValue(2, 3, z);
	

	return translationMatrix * (*this);
}

Mat4 Mat4::scale(float x, float y, float z) const {
	
	Mat4 scaleMatrix(1.0f);
	scaleMatrix.setValue(0, 0, x);
	scaleMatrix.setValue(1, 1, y);
	scaleMatrix.setValue(2, 2, z);

	return scaleMatrix * (*this);
}

Mat4 Mat4::rotate(float radX, float radY, float radZ) const {

	auto identity = Mat4::identity();

	auto cosX = cosf(radX);
	auto cosY = cosf(radY);
	auto cosZ = cosf(radZ);
	auto sinX = sinf(radX);
	auto sinY = sinf(radY);
	auto sinZ = sinf(radZ);

	Mat4 xRotation{
		1, 0, 0, 0,
		0, cosX, -sinX, 0,
		0, sinX, cosX, 0,
		0, 0, 0, 1
	};

	Mat4 yRotation{
		cosY, 0, sinY, 0,
		0, 1, 0, 0,
		-sinY, 0, cosY, 0,
		0, 0, 0, 1
	};

	Mat4 zRotation{
		cosZ, -sinZ, 0, 0,
		sinZ, cosZ, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	return zRotation * (yRotation * xRotation) * (*this);
}

Mat4 Mat4::shear(float xY, float xZ, float yX, float yZ, float zX, float zY) const
{
	return Mat4{
		1, xY, xZ, 0,
		yX, 1, yZ, 0,
		zX, zY, 1, 0,
		0, 0, 0, 1
	} * (*this);
}
