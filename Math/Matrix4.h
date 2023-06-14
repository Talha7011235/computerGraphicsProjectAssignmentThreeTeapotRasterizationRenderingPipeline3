// Computer Graphics Project Assignment 3 Rasterization Rendering Pipeline
// Matrix4.h
#ifndef MATRIX4_H
#define MATRIX4_H

#include "Matrix3.h"
#include "Vector.h"
#include <array>

struct Matrix4
{
public:
    Matrix4();
    Matrix4(const std::array<std::array<float, 4>, 4>&);

    float Determinant() const;
    Matrix4 Inverted() const;
    Matrix4 Transpose() const;

    std::array<float, 4> operator[](const unsigned int&) const;
    Matrix4 operator*(const Matrix4&) const;
    Vector3f operator*(const Vector3f&) const;
    Vector4f operator*(const Vector4f&) const;

    static Matrix4 LookAt(const Vector3f&, const Vector3f&, const Vector3f&);
    static Matrix4 Orthographic(const Vector2f&, const Vector2f&, const Vector2f&);
    static Matrix4 Projection(const Vector2f&, const float&, const float&);
    static Matrix4 ViewPortForProjectThree(const Vector2i&);

    Vector3f getTranslation() const;
    Vector3f getForward() const;
    Matrix3 getRotation() const;

    friend std::ostream& operator << (std::ostream&, const Matrix4&);

private:
    std::array<std::array<float, 4>, 4> data;
};

#endif

