// Computer Graphics Project Assignment 3 Rasterization Rendering Pipeline
// ColorForProjectThree.h
#ifndef COLORFORPROJECTTHREE_H
#define COLORFORPROJECTTHREE_H

#include "../Math/Vector.h"
#include <array>
#include <iostream>
#include <string>

struct ColorForProjectThree : public Vector3f
{
public:
    ColorForProjectThree();
    ColorForProjectThree(const Vector3f&);
    ColorForProjectThree(const float&, const float&, const float&);
    virtual ~ColorForProjectThree();

    std::array<unsigned char, 3> asByteArray() const;
};

#endif

