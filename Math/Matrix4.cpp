// Computer Graphics Project Assignment 3 Rasterization Rendering Pipeline
// Matrix4.cpp
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include "Matrix4.h"
#include "Matrix3.h"
#include <cmath>

Matrix4::Matrix4()
{
	// Identity matrix is
	// [
	//   1 0 0 0
	//   0 1 0 0
	//   0 0 1 0
	//   0 0 0 1
	// ]
	for(int i = 0; i < 4; ++i) {
		std::fill(data[i].begin(), data[i].end(), 0);
		data[i][i] = 1;
	}
}
Matrix4::Matrix4(const std::array<std::array<float, 4>, 4> &right)
{
	for(int i = 0; i < 4; ++i) {
		std::copy(right[i].begin(), right[i].end(), data[i].begin());
	}
}

std::array<float, 4> Matrix4::operator[](const unsigned int& index) const {
	if(index > 3) throw std::out_of_range("Invalid Matrix Row");
	return data[index];
}

float Matrix4::Determinant() const
{
	Matrix3 A{{
		std::array<float, 3>{data[1][1], data[1][2], data[1][3]},
		std::array<float, 3>{data[2][1], data[2][2], data[2][3]},
		std::array<float, 3>{data[3][1], data[3][2], data[3][3]}
	}};

	Matrix3 B{{
		std::array<float, 3>{data[1][0], data[1][2], data[1][3]},
		std::array<float, 3>{data[2][0], data[2][2], data[2][3]},
		std::array<float, 3>{data[3][0], data[3][2], data[3][3]}
	}};

	Matrix3 C{{
		std::array<float, 3>{data[1][0], data[1][1], data[1][3]},
		std::array<float, 3>{data[2][0], data[2][1], data[2][3]},
		std::array<float, 3>{data[3][0], data[3][1], data[3][3]}
	}};

	Matrix3 D{{
		std::array<float, 3>{data[1][0], data[1][1], data[1][2]},
		std::array<float, 3>{data[2][0], data[2][1], data[2][2]},
		std::array<float, 3>{data[3][0], data[3][1], data[3][2]}
	}};

	return data[0][0] * A.Determinant() - data[0][1] * B.Determinant() +
		   data[0][2] * C.Determinant() - data[0][3] * D.Determinant();
}

Matrix4 Matrix4::Inverted() const
{
	float det = Determinant();
	if (det == 0)
	{
		throw std::runtime_error("Cannot Invert 4x4 matrix: Zero Determinant");
	}

	/* Step 1 matrix of minors and cofactors
	 *  0  1  2  3      4*8 - 5*7, -(3*8 - 5*6),  3*7 - 4*6
	 *  4  5  6  7 => -(1*8 - 2*7),  0*8 - 2*6, -(0*7 - 1*6)
	 *  8  9 10 11      5*1 - 2*4, -(0*5 - 2*3),  0*4 - 1*3
	 * 12 13 14 15
	 */

	std::array<std::array<float, 4>, 4> minors;

	// First Row
	minors[0][0] = Matrix3({
		std::array<float, 3>{data[1][1], data[1][2], data[1][3]},
		std::array<float, 3>{data[2][1], data[2][2], data[2][3]},
		std::array<float, 3>{data[3][1], data[3][2], data[3][3]}
	}).Determinant();

	minors[0][1] = Matrix3({
		std::array<float, 3>{data[1][0], data[1][2], data[1][3]},
		std::array<float, 3>{data[2][0], data[2][2], data[2][3]},
		std::array<float, 3>{data[3][0], data[3][2], data[3][3]}
	}).Determinant();

	minors[0][2] = Matrix3({
		std::array<float, 3>{data[1][0], data[1][1], data[1][3]},
		std::array<float, 3>{data[2][0], data[2][1], data[2][3]},
		std::array<float, 3>{data[3][0], data[3][1], data[3][3]}
	}).Determinant();

	minors[0][3] = Matrix3({
		std::array<float, 3>{data[1][0], data[1][1], data[1][2]},
		std::array<float, 3>{data[2][0], data[2][1], data[2][2]},
		std::array<float, 3>{data[3][0], data[3][1], data[3][2]}
	}).Determinant();

	// Second Row
	minors[1][0] = Matrix3({
		std::array<float, 3>{data[0][1], data[0][2], data[0][3]},
		std::array<float, 3>{data[2][1], data[2][2], data[2][3]},
		std::array<float, 3>{data[3][1], data[3][2], data[3][3]}
	}).Determinant();

	minors[1][1] = Matrix3({
		std::array<float, 3>{data[0][0], data[0][2], data[0][3]},
		std::array<float, 3>{data[2][0], data[2][2], data[2][3]},
		std::array<float, 3>{data[3][0], data[3][2], data[3][3]}
	}).Determinant();

	minors[1][2] = Matrix3({
		std::array<float, 3>{data[0][0], data[0][1], data[0][3]},
		std::array<float, 3>{data[2][0], data[2][1], data[2][3]},
		std::array<float, 3>{data[3][0], data[3][1], data[3][3]}
	}).Determinant();

	minors[1][3] = Matrix3({
		std::array<float, 3>{data[0][0], data[0][1], data[0][2]},
		std::array<float, 3>{data[2][0], data[2][1], data[2][2]},
		std::array<float, 3>{data[3][0], data[3][1], data[3][2]}
	}).Determinant();

	// Third Row
	minors[2][0] = Matrix3({
		std::array<float, 3>{data[0][1], data[0][2], data[0][3]},
		std::array<float, 3>{data[1][1], data[1][2], data[1][3]},
		std::array<float, 3>{data[3][1], data[3][2], data[3][3]}
	}).Determinant();

	minors[2][1] = Matrix3({
		std::array<float, 3>{data[0][0], data[0][2], data[0][3]},
		std::array<float, 3>{data[1][0], data[1][2], data[1][3]},
		std::array<float, 3>{data[3][0], data[3][2], data[3][3]}
	}).Determinant();

	minors[2][2] = Matrix3({
		std::array<float, 3>{data[0][0], data[0][1], data[0][3]},
		std::array<float, 3>{data[1][0], data[1][1], data[1][3]},
		std::array<float, 3>{data[3][0], data[3][1], data[3][3]}
	}).Determinant();

	minors[2][3] = Matrix3({
		std::array<float, 3>{data[0][0], data[0][1], data[0][2]},
		std::array<float, 3>{data[1][0], data[1][1], data[1][2]},
		std::array<float, 3>{data[3][0], data[3][1], data[3][2]}
	}).Determinant();

	// Fourth Row
	minors[3][0] = Matrix3({
		std::array<float, 3>{data[0][1], data[0][2], data[0][3]},
		std::array<float, 3>{data[1][1], data[1][2], data[1][3]},
		std::array<float, 3>{data[2][1], data[2][2], data[2][3]}
	}).Determinant();

	minors[3][1] = Matrix3({
		std::array<float, 3>{data[0][0], data[0][2], data[0][3]},
		std::array<float, 3>{data[1][0], data[1][2], data[1][3]},
		std::array<float, 3>{data[2][0], data[2][2], data[2][3]}
	}).Determinant();

	minors[3][2] = Matrix3({
		std::array<float, 3>{data[0][0], data[0][1], data[0][3]},
		std::array<float, 3>{data[1][0], data[1][1], data[1][3]},
		std::array<float, 3>{data[2][0], data[2][1], data[2][3]}
	}).Determinant();

	minors[3][3] = Matrix3({
		std::array<float, 3>{data[0][0], data[0][1], data[0][2]},
		std::array<float, 3>{data[1][0], data[1][1], data[1][2]},
		std::array<float, 3>{data[2][0], data[2][1], data[2][2]}
	}).Determinant();

	float invDet = 1 / det;
	return Matrix4{{
		std::array<float, 4>{ minors[0][0] * invDet,-minors[0][1] * invDet, minors[0][2] * invDet,-minors[0][3] * invDet},
		std::array<float, 4>{-minors[1][0] * invDet, minors[1][1] * invDet,-minors[1][2] * invDet, minors[1][3] * invDet},
		std::array<float, 4>{ minors[2][0] * invDet,-minors[2][1] * invDet, minors[2][2] * invDet,-minors[2][3] * invDet},
		std::array<float, 4>{-minors[3][0] * invDet, minors[3][1] * invDet,-minors[3][2] * invDet, minors[3][3] * invDet},
	}};
}

Matrix4 Matrix4::Transpose() const
{
	return {{ 
		std::array<float, 4>{data[0][0], data[1][0], data[2][0], data[3][0]},
		std::array<float, 4>{data[0][1], data[1][1], data[2][1], data[3][1]},
		std::array<float, 4>{data[0][2], data[1][2], data[2][2], data[3][2]},
		std::array<float, 4>{data[0][3], data[1][3], data[2][3], data[3][3]}
	}};
}

Matrix4 Matrix4::operator*(const Matrix4 &right) const
{
	/*
		[a b] [e f] = [ab(eg), ab(fh)]
		[c d] [g h] = [cd(eg), cd(fh)]
	*/
	Matrix4 rTranspose = right.Transpose();
	return Matrix4{{
		std::array<float, 4>{Vector4f::dot(data[0], rTranspose.data[0]), Vector4f::dot(data[0], rTranspose.data[1]), Vector4f::dot(data[0], rTranspose.data[2]), Vector4f::dot(data[0], rTranspose.data[3])},
		std::array<float, 4>{Vector4f::dot(data[1], rTranspose.data[0]), Vector4f::dot(data[1], rTranspose.data[1]), Vector4f::dot(data[1], rTranspose.data[2]), Vector4f::dot(data[1], rTranspose.data[3])},
		std::array<float, 4>{Vector4f::dot(data[2], rTranspose.data[0]), Vector4f::dot(data[2], rTranspose.data[1]), Vector4f::dot(data[2], rTranspose.data[2]), Vector4f::dot(data[2], rTranspose.data[3])},
		std::array<float, 4>{Vector4f::dot(data[3], rTranspose.data[0]), Vector4f::dot(data[3], rTranspose.data[1]), Vector4f::dot(data[3], rTranspose.data[2]), Vector4f::dot(data[3], rTranspose.data[3])}
	}};
}
Vector3f Matrix4::operator*(const Vector3f &right) const
{
	Vector4f rV = {{right[0], right[1], right[2], 1}};
	float W = Vector4f::dot(data[3], rV);
	if(W != 0) {
		return Vector3f({
			Vector4f::dot(data[0], rV) / W,
			Vector4f::dot(data[1], rV) / W,
			Vector4f::dot(data[2], rV) / W
		});
	}
	return Vector3f({
		Vector4f::dot(data[0], rV),
		Vector4f::dot(data[1], rV),
		Vector4f::dot(data[2], rV)
	});
}
Vector4f Matrix4::operator*(const Vector4f &right) const
{
	return Vector4f({
		Vector4f::dot(data[0], right),
		Vector4f::dot(data[1], right),
		Vector4f::dot(data[2], right),
		Vector4f::dot(data[3], right)
	});
}

Vector3f Matrix4::getTranslation() const {
	return Vector3f{{-data[0][3] / data[3][3], -data[1][3] / data[3][3], -data[2][3] / data[3][3]}};
}

Vector3f Matrix4::getForward() const {
	return Vector3f{{data[0][2], data[1][2], data[2][2]}};
}

Matrix3 Matrix4::getRotation() const {
	return Matrix3{{
		std::array<float, 3>{data[0][0], data[0][1], data[0][2]},
		std::array<float, 3>{data[1][0], data[1][1], data[1][2]},
		std::array<float, 3>{data[2][0], data[2][1], data[2][2]}
	}};
}

Matrix4 Matrix4::LookAt(const Vector3f &from, const Vector3f &at, const Vector3f &up)
{
	Vector3f forward = Vector3f::invert(Vector3f::normalize(at - from));
	Vector3f right = Vector3f::invert(Vector3f::normalize(Vector3f::cross(up, forward)));
	Vector3f newUp = Vector3f::invert(Vector3f::cross(forward, right));

	float newX = Vector3f::dot(right, from);
	float newY = Vector3f::dot(newUp, from);
	float newZ = Vector3f::dot(forward, from);

	return Matrix4{{
		std::array<float, 4>{  right[0],   right[1],   right[2], -newX},
		std::array<float, 4>{  newUp[0],   newUp[1],   newUp[2], -newY},
		std::array<float, 4>{forward[0], forward[1], forward[2], -newZ},
		std::array<float, 4>{   0,    0,      0, 1}
	}};
}

Matrix4 Matrix4::Orthographic(const Vector2f& horizontal, const Vector2f& vertical, const Vector2f& depth) {
	float rPL = horizontal[1] + horizontal[0];
	float tPB = vertical[1] + vertical[0];
	float nPF = depth[0] + depth[1];
	float rL = horizontal[1] - horizontal[0];
	float tB = vertical[1] - vertical[0];
	float nF = depth[0] - depth[1];

	return Matrix4{{
		std::array<float, 4>{2.f / rL,        0,        0, -rPL / rL},
		std::array<float, 4>{       0, 2.f / tB,        0, -tPB / tB},
		std::array<float, 4>{       0,        0, 2.f / nF, -nPF / nF},
		std::array<float, 4>{       0,        0,        0,         1}
	}};
}

Matrix4 Matrix4::Projection(const Vector2f& depth, const float& angle, const float& aspectRatio)
{
	float tTheta = tan(angle * 0.5f * M_PI /180.f);

	float n = depth[0];
	float f = depth[1];

	float t = tTheta * n;
	float r = aspectRatio * t;
	float q = (f + n) / (n - f);

	return Matrix4{{
		std::array<float, 4>{ (2*n)/(2*r),            0,  0,  0},
		std::array<float, 4>{           0,  (2*n)/(2*t),  0,  0},
		std::array<float, 4>{           0,            0,  q, (2*f*n)/(f-n)},
		std::array<float, 4>{           0,            0,  1,  0}
	}};
}

Matrix4 Matrix4::ViewPortForProjectThree(const Vector2i& resolution) {
	float nx = resolution[0];
	float ny = resolution[1];
	return Matrix4{{
		std::array<float, 4>{nx / 2,      0,       0, (nx - 1)/2},
		std::array<float, 4>{     0, ny / 2,       0, (ny - 1)/2},
		std::array<float, 4>{     0,      0,       1,          0},
		std::array<float, 4>{     0,      0,       0,          0}
	}};
}

std::ostream& operator << (std::ostream& out, const Matrix4& value) {
	out << value.data[0][0] << ", " << value.data[0][1] << ", " << value.data[0][2] << ", " << value.data[0][3] << std::endl;
	out << value.data[1][0] << ", " << value.data[1][1] << ", " << value.data[1][2] << ", " << value.data[1][3] << std::endl;
	out << value.data[2][0] << ", " << value.data[2][1] << ", " << value.data[2][2] << ", " << value.data[2][3] << std::endl;
	out << value.data[3][0] << ", " << value.data[3][1] << ", " << value.data[3][2] << ", " << value.data[3][3] << std::endl;
	return out;
}
