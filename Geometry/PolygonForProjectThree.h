// Computer Graphics Project Assignment 3 Rasterization Rendering Pipeline
// PolygonForProjectThree.h
#ifndef POLYGONFORPROJECTTHREE_H
#define POLYGONFORPROJECTTHREE_H

#include "../Elements/ShadingForProjectThree.h"
#include "../Math/Vector.h"
#include "Renderable.h"
#include "Triangle.h"
#include <vector>
#include <array>

// The Structure Data Type "struct Polygon" represents the implementation of a n point Polygon, tesellated into triangles using a custom method.
struct PolygonForProjectThree : public Renderable
{
public:
    PolygonForProjectThree();
    ~PolygonForProjectThree();

    int getCount() const;
    std::vector<Vector3f> getVerticies() const;
    std::vector<Vector3f> getNormals() const;
    virtual std::vector<Triangle> getTriangles() const;
    virtual int getType() const;
    void setShading(ShadingForProjectThree);

    friend std::istream& operator>> (std::istream&, PolygonForProjectThree&);
private:
    bool IntersectTriangle(const int, const int, const int, Vector3f, Vector3f, float&, Vector3f&) const;
    int count;
    std::vector<Vector3f> verticies;
    std::vector<Vector3f> normals;
    std::vector<int> indicies;
    ShadingForProjectThree shading;
};

#endif

