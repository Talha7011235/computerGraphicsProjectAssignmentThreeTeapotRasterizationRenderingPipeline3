// Computer Graphics Project Assignment 3 Rasterization Rendering Pipeline
// Matrix3.h
#ifndef MATRIX3_H
#define MATRIX3_H

#include "Vector.h"
#include <array>

struct Matrix3
{
public:
    Matrix3();
    Matrix3(const std::array<std::array<float, 3>, 3>&);

    void Set(const int&, const int&, const float&);

    void LookAt(const Vector3f&, const Vector3f&, const Vector3f&);
    Vector3f RotateVector(const Vector3f&) const;

    float Determinant() const;
    Matrix3 Inverted() const;
    Matrix3 Transpose() const;

    Matrix3 operator*(const Matrix3&) const;
    Vector3f operator*(const Vector3f&) const;

private:
    std::array<std::array<float, 3>, 3> data;
};

#endif

