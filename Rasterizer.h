// Computer Graphics Project Assignment 3 Rasterization Rendering Pipeline
// Rasterizer.h
#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "Math/Vector.h"
#include "Math/Matrix4.h"
#include "Elements/ColorForProjectThree.h"
#include "Elements/LightForProjectThree.h"
#include "Geometry/Plane.h"
#include "Geometry/Triangle.h"
#include <array>
#include <vector>

class Rasterizer
{
public:
    Rasterizer(const Vector2i& resolution, const ColorForProjectThree&);
    ~Rasterizer();

    void DrawLine(const Vector2i&, const Vector2i&, const ColorForProjectThree&);
    void DrawSquare(const Vector2i&, const Vector2i&, const ColorForProjectThree&);
    void DrawTriangle(const std::array<Vector2i, 3>&, const ColorForProjectThree&);
    void DrawFilledSquare(const Vector2i&, const Vector2i&, const ColorForProjectThree&);

    void RenderTriangle(const Triangle&);

    void RenderDepthMap(LightForProjectThree&, const std::vector<Triangle>&);

    void ProcessVertices(std::vector<Triangle>&) const;
    std::vector<Triangle> Clipping(const std::vector<Triangle>&);
    void Rasterize(const std::vector<Triangle>&);
    ColorForProjectThree ProcessFragment(const unsigned int&, const Triangle&, const Vector3f&, const Vector3f&);
    void Blending(const unsigned int&, const float&, const ColorForProjectThree&);

    std::vector<ColorForProjectThree> getPixels() const;
    std::vector<LightForProjectThree> getLights() const;

    void SetLights(const std::vector<LightForProjectThree>&);
    void SetCamera(const Matrix4&);
    void SetProjection(const Matrix4&);
    void SetViewPort(const Matrix4&);
    void SetEye(const Vector3f&);
    void SetFragment(const bool&);

private:
    void GenerateFrustum();
    std::vector<Triangle> ClipToPlane(const std::vector<Triangle>&, const Plane&);

    Matrix4 projection;
    Matrix4 camera;
    Matrix4 viewPort;

    std::vector<LightForProjectThree> lights;
    std::vector<ColorForProjectThree> image;
    std::vector<float> depth;
    Vector2i resolution;
    Vector3f eye;

    bool fragment;

    std::array<Plane, 5> frustum;
};


#endif
