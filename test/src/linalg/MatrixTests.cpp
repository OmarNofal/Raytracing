#include <linalg/Matrix.h>
#include <gtest/gtest.h>
#include <vec/Tuple.h>



TEST(MatrixTests, MatrixInit) {

	Matrix m(2, 1, 2.0f);

	EXPECT_EQ(m.numColumns, 1);
	EXPECT_EQ(m.numRows, 2);

	for (int i = 0; i < m.numRows; i++) {
		for (int j = 0; j < m.numColumns; j++) {
			EXPECT_EQ(m.getValueAt(i, j), 2.0f);
		}
	}

}


TEST(MatrixTests, MatrixInitializerList) {

	Matrix m(3, 3, {1.0f, 2.2f, 1.2f, 0.2f, 2.3f});

	EXPECT_EQ(m.getValueAt(0, 1), 2.2f);
	EXPECT_EQ(m.getValueAt(1, 1), 2.3f);
	EXPECT_EQ(m.getValueAt(2, 2), 0.0f);

}

TEST(MatrixTests, SpecialMatrixInit) {

	Mat2 m2 = Mat2::identity();
	EXPECT_EQ(m2.numColumns, 2);
	EXPECT_EQ(m2.numRows, 2);
	EXPECT_EQ(m2.getValueAt(0, 0), 1.0f);

	Mat3 m3(2.0f);
	EXPECT_EQ(m3.getValueAt(0, 0), 2.0f);
	EXPECT_EQ(m3.getValueAt(1, 1), 2.0f);
	EXPECT_EQ(m3.getValueAt(1, 1), 2.0f);
	EXPECT_EQ(m3.getValueAt(1, 2), 0.0f);

	Mat4 m4(2.0f);
	EXPECT_EQ(m4.getValueAt(0, 0), 2.0f);
	EXPECT_EQ(m4.getValueAt(1, 1), 2.0f);
	EXPECT_EQ(m4.getValueAt(2, 2), 2.0f);
	EXPECT_EQ(m4.getValueAt(3, 3), 2.0f);
	EXPECT_EQ(m4.getValueAt(0, 2), 0.0f);

}

TEST(MatrixTests, MatrixComparison) {

	Mat3 m31(2.0f);
	Mat3 m32(2.0f);

	EXPECT_TRUE(m31 == m32);

	m32.setValue(1, 2, 3.0f);
	EXPECT_FALSE(m31 == m32);

	// test float inaccuracies
	m32.setValue(1, 2, 0.000001f);
	EXPECT_TRUE(m31 == m32);
}

TEST(MatrixTests, SimpleMatrixMultiplication) {
	Matrix m1(2, 3, {
		1, 2, 3,
		4, 5, 6
		});

	Matrix m2(3, 2, {
		1, 2,
		3, 4,
		5, 6
		});

	Matrix expected(2, 2, {
		22, 28,
		49, 64
		});

	EXPECT_EQ(m1 * m2, expected);
}

TEST(MatrixTests, Mat4Multiplication) {

	Mat4 m1{
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 8, 7, 6,
		5, 4, 3, 2
	};

	Mat4 m2{
		-2, 1, 2, 3,
		3, 2, 1, -1,
		4, 3, 6, 5,
		1, 2, 7, 8
	};

	Mat4 expectedResult{
		20, 22, 50, 48,
		44, 54, 114, 108,
		40, 58, 110, 102,
		16, 26, 46, 42
	};

	EXPECT_TRUE(m1 * m2 == expectedResult);

}


TEST(MatrixTests, MatrixTimesTuple) {

	Tuple t{ 1, 2, 3, 1 };
	Mat4 m{
		1, 2, 3, 4,
		2, 4, 4, 2,
		8, 6, 4, 1,
		0, 0, 0, 1
	};

	Tuple result{18, 24, 33, 1};

	EXPECT_EQ(m * t, result);
}


TEST(MatrixTests, MatrixTimesIdentity) {
	Mat4 id = Mat4::identity();
	Mat4 m({ 1, 2, 3, 4 , 5, 6, 7, 8});
	EXPECT_EQ(m * id, m);
}


TEST(MatrixTests, IdentityTimesTuple) {
	Mat4 id = Mat4::identity();
	Tuple t{1, 8, 7, 2};
	EXPECT_EQ(id * t, t);
}


TEST(MatrixTests, MatrixTranspose) {
	Mat4 m{
		1, 9, 3, 0,
		9, 8, 0, 8,
		1, 8, 5, 3,
		0, 0, 5, 8
	};

	Mat4 t{
		1, 9, 1, 0,
		9, 8, 8, 0,
		3, 0, 5, 5,
		0, 8, 3, 8
	};

	EXPECT_EQ(m.transpose(), t);

}


TEST(MatrixTests, IdentityTranspose) {
	Mat4 m = Mat4::identity();
	EXPECT_EQ(m.transpose(), m);
}


TEST(MatrixTests, Mat2Det) {
	Mat2 m{
		1, 5,
		-3, 2
	};
	EXPECT_EQ(m.determinant(), 17.0f);
}

TEST(MatrixTests, SubMatrix) {

	Mat3 m3{
		1, 5, 0,
		-3, 2, 7,
		0, 6, -3
	};
	
	Mat2 expected1{
		-3, 2,
		0, 6
	};

	EXPECT_EQ(m3.subMatrix(0, 2), expected1);


	Mat4 m4{
		-6, 1, 1, 6,
		-8, 5, 8, 6,
		-1, 0, 8, 2,
		-7, 1, -1, 1
	};

	Mat3 expected2{
		-6, 1, 6,
		-8, 8, 6,
		-7, -1, 1
	};

	Mat3 expected3{
		1, 1, 6,
		5, 8, 6,
		0, 8, 2
	};

	EXPECT_EQ(m4.subMatrix(2, 1), expected2);
	EXPECT_EQ(m4.subMatrix(3, 0), expected3);
}


TEST(MatrixTests, MinorTest) {

	Mat3 m{
		3, 5, 0,
		2, -1, 7,
		6, -1, 5
	};

	auto minor = m.minor(1, 0);

	EXPECT_EQ(minor, 25);
}

TEST(MatrixTests, CofactorTest) {

	Mat3 m{
		3, 5, 0,
		2, -1, -7,
		6, -1, 5
	};

	EXPECT_EQ(m.cofactor(0, 0), -12.0f);
	EXPECT_EQ(m.cofactor(1, 0), -25.0f);
}

TEST(MatrixTests, Mat3Determinant) {

	Mat3 m{
		1, 2, 6,
		-5, 8, -4,
		2, 6, 4
	};

	EXPECT_EQ(m.determinant(), -196.0f);

}

TEST(MatrixTests, Mat4Determinant) {

	Mat4 m{
		-2, -8, 3, 5,
		-3, 1, 7, 3,
		1, 2, -9, 6,
		-6, 7, 7, -9
	};

	Mat3 e1{
		1, 7, 3,
		2, -9, 6,
		7, 7, -9
	};
	EXPECT_EQ(m.subMatrix(0, 0), e1);

	EXPECT_EQ(m.determinant(), -4071.0f);
	EXPECT_EQ(m.cofactor(0, 0), 690.0f);
}

TEST(MatrixTests, Mat4Inverse) {

	Mat4 m{
		8, -5, 9, 2,
		7, 5, 6, 1,
		-6, 0, 9, 6,
		-3, 0, -9, -4
	};

	Mat4 inverse{
		-0.15385f, -0.15385f, -0.28205f, -0.53846,
		-0.07692, 0.12308f, 0.02564f, 0.03077f,
		0.35897f, 0.35897f, 0.43590f, 0.92308f,
		-0.69231, -0.69231f, -0.76923f, -1.92308f
	};

	EXPECT_EQ(m.inverse(), inverse);
	
}


TEST(MatrixTests, Mat4Invertibility) {

	Mat4 m{
		3, -9, 7, 3,
		3, -8, 2, -9,
		-4, 4, 4, 1,
		-6, 5, -1, 1
	};

	Mat4 v{
		8, 2, 2, 2,
		3, -1, 7, 0,
		7, 0, 5, 4,
		6, -2, 0, 5
	};

	auto c = m * v;

	EXPECT_EQ(c * v.inverse(), m);

}