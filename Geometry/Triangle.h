// Computer Graphics Project Assignment 3 Rasterization Rendering Pipeline
// Triangle.h
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../Math/Vector.h"
#include "../Math/Matrix4.h"
#include "../Elements/ColorForProjectThree.h"
#include "../Elements/LightForProjectThree.h"
#include "../Elements/ShadingForProjectThree.h"
#include <array>
#include <vector>

struct Triangle {
public:
    Triangle(const std::array<Vector3f, 3>&, const std::array<Vector3f, 3>&, const ShadingForProjectThree&);
    Triangle(const std::array<Vector3f, 3>&, const std::array<Vector3f, 3>&, const ShadingForProjectThree&, const std::array<ColorForProjectThree, 3>&);
    ~Triangle();

    std::array<Vector3f, 3> getVertices() const;
    std::array<Vector3f, 3> getNormals() const;
    std::array<ColorForProjectThree, 3> getColors() const;
    std::array<std::vector<Vector3f>, 3> getLightDirections() const;
    ShadingForProjectThree getShading() const;

    void setColors(const std::array<ColorForProjectThree, 3>&);
    void light(const std::vector<LightForProjectThree>&, const Vector3f&);
    void transform(const Matrix4&);

private:
    std::array<Vector3f, 3> vertices;
    std::array<Vector3f, 3> normals;
    std::array<ColorForProjectThree, 3> colors;
    std::array<std::vector<Vector3f>, 3> lightDirections;
    ShadingForProjectThree shading;
};

#endif
