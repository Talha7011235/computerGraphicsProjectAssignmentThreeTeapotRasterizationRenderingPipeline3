// Computer Graphics Project Assignment 3 Rasterization Rendering Pipeline
// Renderable.h
#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "../Math/Vector.h"
#include "../Elements/ShadingForProjectThree.h"
#include "Triangle.h"
#include <vector>

struct Renderable
{
public:
    virtual int getType() const = 0;
    virtual std::vector<Triangle> getTriangles() const = 0;
};

#endif

