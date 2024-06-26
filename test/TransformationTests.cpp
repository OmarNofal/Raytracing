#include <linalg/Matrix.h>
#include <vec/Tuple.h>
#include <gtest/gtest.h>

#define _USE_MATH_DEFINES
#include <math.h>


TEST(TransformationTests, TranslatePoint) {
	
	Mat4 translationMatrix = Mat4::identity()
		.translate(5, -3, 2);

	Tuple p = Tuple::createPoint(-3, 4, 5);

	Tuple expected = Tuple::createPoint(2, 1, 7);
	EXPECT_EQ(translationMatrix * p, expected);
	EXPECT_EQ(translationMatrix.inverse() * expected, p);
}

TEST(TransformationTests, ScaleTuple) {

	Mat4 scaleMatrix = Mat4::identity()
		.scale(2, -3, 4);

	Tuple p = Tuple::createPoint(-3, 4, 5);

	Tuple v = Tuple::createVector(0, 1, 2);

	Tuple expectedPoint = Tuple::createPoint(-6, -12, 20);
	Tuple expectedVector = Tuple::createVector(0, -3, 8);
	
	EXPECT_EQ(scaleMatrix * p, expectedPoint);
	EXPECT_EQ(scaleMatrix * v, expectedVector);
}

TEST(TransformationTests, TranslateVectorShouldntMove) {

	Mat4 translationMatrix = Mat4::identity()
		.translate(5, -3, 2);

	Tuple p = Tuple::createVector(-3, 4, 5);

	EXPECT_EQ(translationMatrix * p, p);
}

TEST(TransformationTests, RotatePoint) {

	auto p = Tuple::createPoint(0, 1, 0);

	auto rotationMatrix = Mat4::identity()
		.rotate(M_PI / 4.0f, 0, 0);

	EXPECT_EQ(rotationMatrix * p, Tuple::createPoint(0, sqrtf(2.0f) / 2.0f, sqrtf(2.0f) / 2.0f));
	EXPECT_EQ(rotationMatrix.inverse() * p, Tuple::createPoint(0, sqrtf(2.0f) / 2.0f, -sqrtf(2.0f) / 2.0f));

	auto rot2 = Mat4::identity()
		.rotate(M_PI / 2.0f, 0, 0);

	EXPECT_EQ(rot2 * p, Tuple::createPoint(0, 0, 1));


	auto rotY = Mat4::identity()
		.rotate(0, M_PI, 0);

	auto p2 = Tuple::createPoint(2, 0, 0);

	EXPECT_EQ(rotY * p, Tuple::createPoint(0, 1, 0));
	EXPECT_EQ(rotY * p2, Tuple::createPoint(-2, 0, 0));

	
	auto rotZ = Mat4::identity()
		.rotate(0, 0, M_PI / 2.0f);

	EXPECT_EQ(rotZ * p, Tuple::createPoint(-1, 0, 0));
	EXPECT_EQ(rotZ * p2, Tuple::createPoint(0, 2, 0));

}

TEST(TransformationTests, ShearPoint) {

	auto p = Tuple::createPoint(2, 3, 4);
	auto shearMatrixX = Mat4::identity()
		.shear(0, 1, 0, 0, 0, 0);

	auto shearMatrixY = Mat4::identity()
		.shear(0, 0, 1, 0, 0, 0);

	auto shearMatrixZ = Mat4::identity()
		.shear(0, 0, 0, 0, 0, 1);


	EXPECT_EQ(shearMatrixX * p, Tuple::createPoint(6, 3, 4));
	EXPECT_EQ(shearMatrixY * p, Tuple::createPoint(2, 5, 4));
	EXPECT_EQ(shearMatrixZ * p, Tuple::createPoint(2, 3, 7));

}


TEST(TransformationTests, ChainingTransformations) {

	Tuple p = Tuple::createPoint(1, 0, 1);

	auto mat = Mat4::identity()
		.rotate(M_PI / 2, 0, 0)
		.scale(5, 5, 5)
		.translate(10, 5, 7);

	EXPECT_EQ(mat * p, Tuple::createPoint(15, 0, 7));


}


TEST(TransformationTests, ViewMatrix) {

	Tuple from = Tuple::createPoint(0, 0, 0);
	Tuple to = Tuple::createPoint(0, 0, -1);
	Tuple up = Tuple::createVector(0, 1, 0);

	auto m = viewMatrix(from, to, up);

	EXPECT_EQ(m, Mat4(1.0f));

	Tuple to2 = Tuple::createPoint(0, 0, 1);

	auto m2 = viewMatrix(from, to2, up);
	EXPECT_EQ(m2, Mat4(1.0f).scale(-1, 1, -1));

}

TEST(TransformationTests, ViewMatrixMovesWorld) {

	Tuple from = Tuple::createPoint(0, 0, 8);
	Tuple to = Tuple::createPoint(0, 0, 0);
	Tuple up = Tuple::createVector(0, 1, 0);

	auto m = viewMatrix(from, to, up);
	EXPECT_EQ(m, Mat4(1.0f).translate(0, 0, -8));

}

TEST(TransformationTests, ViewMatrixAribitraryPosition) {

	Tuple from = Tuple::createPoint(1, 3, 2);
	Tuple to = Tuple::createPoint(4, -2, 8);
	Tuple up = Tuple::createVector(1, 1, 0);

	auto m = viewMatrix(from, to, up);
	
	auto expected = Mat4{
		-0.50709, 0.50709, 0.67612, -2.36643,
		0.76772, 0.60609, 0.12122, -2.82843,
		-0.35857, 0.59761, -0.71714, 0.00000,
		0.00000, 0.00000, 0.00000, 1.00000
	};

	EXPECT_EQ(m, expected);

}