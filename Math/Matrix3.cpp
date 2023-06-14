// Computer Graphics Project Assignment 3 Rasterization Rendering Pipeline
// Matrix3.cpp
#include "Matrix3.h"

Matrix3::Matrix3()
{
	// Identity matrix is 
	// [
	//   1 0 0 0
	//   0 1 0 0
	//   0 0 1 0
	//   0 0 0 1
	// ]
	for(int i = 0; i < 3; ++i) {
		std::fill(data[i].begin(), data[i].end(), 0);
		data[i][i] = 1;
	}
}

Matrix3::Matrix3(const std::array<std::array<float, 3>, 3>& right) {
	for(int i = 0; i < 3; ++i) {
		std::copy(right[i].begin(), right[i].end(), data[i].begin());
	}
}

float Matrix3::Determinant() const {
    return data[0][0] * (data[1][1] * data[2][2] - data[1][2] * data[2][1]) -
           data[0][1] * (data[1][0] * data[2][2] - data[1][2] * data[2][0]) +
           data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);
}

Matrix3 Matrix3::Inverted() const {
    float det = Determinant();
    if(det == 0) {
        throw std::runtime_error("Can not Invert 3x3 matrix: Zero Determinant");
    }

	// 0 3 6   [0][0] [0][1] [0][2]
	// 1 4 7 = [1][0] [1][1] [1][2]
	// 2 5 8   [2][0] [2][1] [2][2]

    float invDet = 1 / det;
    return {{
         (data[1][1] * data[2][2] - data[2][1] * data[1][2]) * invDet,
        -(data[1][0] * data[2][2] - data[2][0] * data[1][2]) * invDet,
         (data[2][1] * data[1][0] - data[2][0] * data[1][1]) * invDet,

        -(data[0][1] * data[2][2] - data[2][1] * data[0][2]) * invDet,
         (data[0][0] * data[2][2] - data[2][0] * data[0][2]) * invDet,
        -(data[0][0] * data[2][1] - data[2][0] * data[0][1]) * invDet,

         (data[0][1] * data[1][2] - data[1][1] * data[0][2]) * invDet,
        -(data[0][0] * data[1][2] - data[1][0] * data[0][2]) * invDet,
         (data[0][0] * data[1][1] - data[1][0] * data[0][1]) * invDet 
    }};
}

Matrix3 Matrix3::Transpose() const {
    return {{
        data[0][0], data[1][0], data[2][0],
        data[0][1], data[1][1], data[2][1],
        data[0][2], data[1][2], data[2][2]
    }};
}

void Matrix3::LookAt(const Vector3f& from, const Vector3f& at, const Vector3f& up)
{

	Vector3f forward = Vector3f::normalize(from - at);
	Vector3f right = Vector3f::normalize(Vector3f::cross(up, forward));
	Vector3f newUp = Vector3f::cross(forward, right);

	data[0][0] = right[0]; data[0][1] = newUp[0]; data[0][2] = forward[0];
	data[1][0] = right[1]; data[1][1] = newUp[1]; data[1][2] = forward[1];
	data[2][0] = right[2]; data[2][1] = newUp[2]; data[2][2] = forward[2];
}

Vector3f Matrix3::RotateVector(const Vector3f& source) const
{
	// Transform a direction with rotation. Transform a direction with no translation.
	float x = source[0] * data[0][0] + source[1] * data[0][1] + source[2] * data[0][2];
	float y = source[0] * data[1][0] + source[1] * data[1][1] + source[2] * data[1][2];
	float z = source[0] * data[2][0] + source[1] * data[2][1] + source[2] * data[2][2];

	return {{ x, y, z }};
}

Matrix3 Matrix3::operator*(const Matrix3& right) const {
	/*
		[a b] [e f] = [ab(eg), ab(fh)]
		[c d] [g h] = [cd(eg), cd(fh)]
	*/

	// Create Columns from the multiplied matrix
	Matrix3 rTranspose = right.Transpose();

	return Matrix3({
		Vector3f::dot(data[0], rTranspose.data[0]), Vector3f::dot(data[0], rTranspose.data[1]), Vector3f::dot(data[0], rTranspose.data[2]),
		Vector3f::dot(data[1], rTranspose.data[0]), Vector3f::dot(data[1], rTranspose.data[1]), Vector3f::dot(data[1], rTranspose.data[2]),
		Vector3f::dot(data[2], rTranspose.data[0]), Vector3f::dot(data[2], rTranspose.data[1]), Vector3f::dot(data[2], rTranspose.data[2])
	});
}
Vector3f Matrix3::operator*(const Vector3f& right) const {
	return Vector3f({
		Vector3f::dot(data[0], right),
		Vector3f::dot(data[1], right),
		Vector3f::dot(data[2], right)
	});
}
