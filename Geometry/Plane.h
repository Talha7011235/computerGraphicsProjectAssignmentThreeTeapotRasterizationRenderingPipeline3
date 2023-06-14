// Computer Graphics Project Assignment 3 Rasterization Rendering Pipeline
// Plane.h
#ifndef PLANE_H
#define PLANE_H

#include "../Math/Vector.h"
#include "../Math/Matrix4.h"
#include "Triangle.h"
#include <iostream>
#include <vector>

struct Plane {
public:
    Plane();
    Plane(const Vector4f&);
    Plane(const Vector3f&, const float&);
    ~Plane();

    void transform(const Matrix4&);
    std::vector<Triangle> clipTriangle(const Triangle&) const;

    friend std::ostream& operator<< (std::ostream&, const Plane&);
private:
    Vector3f intersection(const Vector3f&, const Vector3f&) const;
    Vector3f normal;
    float distance;
};

#endif
