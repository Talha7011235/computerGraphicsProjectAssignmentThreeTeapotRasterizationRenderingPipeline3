// Computer Graphics Project Assignment 3 Rasterization Rendering Pipeline
// Rasterizer.cpp
#include "Rasterizer.h"
#include <algorithm>
#include <cmath>
#include <vector>

Rasterizer::Rasterizer(const Vector2i &resolution, const ColorForProjectThree &defaultColor) : frustum(), fragment(false)
{
    image.resize(resolution[0] * resolution[1]);
    std::fill(image.begin(), image.end(), defaultColor);
    depth.resize(resolution[0] * resolution[1]);
    std::fill(depth.begin(), depth.end(), -std::numeric_limits<float>::max());
    this->resolution = resolution;
}

Rasterizer::~Rasterizer()
{
}

void Rasterizer::DrawLine(const Vector2i &v1, const Vector2i &v2, const ColorForProjectThree &color)
{
    int x0 = v1[0];
    int y0 = v1[1];

    int x1 = v2[0];
    int y1 = v2[1];

    int distX = abs(x1 - x0);
    int distY = abs(y1 - y0);

    if (distY > distX)
    {
        if (y1 < y0)
        {
            std::swap(x0, x1);
            std::swap(y0, y1);
        }

        for (int y = y0; y <= y1; y++)
        {
            float t = (y - y0) / (float)(distY);
            int x = x0 * (1.f - t) + x1 * t;

            int pixel = y * resolution[0] + x;
            if (pixel > 0 && pixel < image.size())
            {
                image[y * resolution[0] + x] = color;
            }
        }
        return;
    }

    if (x1 < x0)
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    for (int x = x0; x <= x1; x++)
    {
        float t = (x - x0) / (float)(distX);
        int y = y0 * (1.f - t) + y1 * t;

        int pixel = y * resolution[0] + x;
        if (pixel > 0 && pixel < image.size())
        {
            image[y * resolution[0] + x] = color;
        }
    }
}

void Rasterizer::DrawSquare(const Vector2i &topLeft, const Vector2i &bottomRight, const ColorForProjectThree &color)
{
    int x0 = topLeft[0];
    int y0 = topLeft[1];

    int x1 = bottomRight[0];
    int y1 = bottomRight[1];

    if (x1 < x0)
    {
        std::swap(x0, x1);
    }
    if (y1 < y0)
    {
        std::swap(y0, y1);
    }

    DrawLine({{x0, y0}}, {{x1, y0}}, color);
    DrawLine({{x1, y0}}, {{x1, y1}}, color);
    DrawLine({{x1, y1}}, {{x0, y1}}, color);
    DrawLine({{x0, y1}}, {{x0, y0}}, color);
}

void Rasterizer::DrawTriangle(const std::array<Vector2i, 3> &points, const ColorForProjectThree &c)
{
    Vector2i Min = {{std::numeric_limits<int>::max(),
                     std::numeric_limits<int>::max()}};
    Vector2i Max = {{-std::numeric_limits<int>::max(),
                     -std::numeric_limits<int>::max()}};
    Vector2i Clamp = {{resolution[0] - 1,
                       resolution[1] - 1}};

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            Min[j] = std::max(0, std::min(Min[j], points[i][j]));
            Max[j] = std::min(Clamp[j], std::max(Max[j], points[i][j]));
        }
    }

    DrawLine(points[0], points[1], c);
    DrawLine(points[1], points[2], c);
    DrawLine(points[2], points[0], c);
}

void Rasterizer::DrawFilledSquare(const Vector2i &topLeft, const Vector2i &bottomRight, const ColorForProjectThree &color)
{
    int x0 = topLeft[0];
    int y0 = topLeft[1];

    int x1 = bottomRight[0];
    int y1 = bottomRight[1];

    if (x1 < x0)
    {
        std::swap(x0, x1);
    }
    if (y1 < y0)
    {
        std::swap(y0, y1);
    }

    for (int y = y0; y <= y1; ++y)
    {
        DrawLine({{x0, y}}, {{x1, y}}, color);
    }
}

Vector3f barycentric(const std::array<Vector3f, 3> &points, const float &pointX, const float &pointY)
{
    float y01 = points[0][1] - points[1][1];
    float y12 = points[1][1] - points[2][1];
    float y20 = points[2][1] - points[0][1];

    float x10 = points[1][0] - points[0][0];
    float x21 = points[2][0] - points[1][0];
    float x02 = points[0][0] - points[2][0];

    float x0y1 = points[0][0] * points[1][1];
    float x1y2 = points[1][0] * points[2][1];
    float x2y0 = points[2][0] * points[0][1];

    float x1y0 = points[1][0] * points[0][1];
    float x2y1 = points[2][0] * points[1][1];
    float x0y2 = points[0][0] * points[2][1];

    float f12XY = y12 * pointX + x21 * pointY + x1y2 - x2y1;
    float f20XY = y20 * pointX + x02 * pointY + x2y0 - x0y2;
    float f01XY = y01 * pointX + x10 * pointY + x0y1 - x1y0;

    float f12X0Y0 = y12 * points[0][0] + x21 * points[0][1] + x1y2 - x2y1;
    float f20X1Y1 = y20 * points[1][0] + x02 * points[1][1] + x2y0 - x0y2;
    float f01X2Y2 = y01 * points[2][0] + x10 * points[2][1] + x0y1 - x1y0;

    return Vector3f{{f12XY / f12X0Y0,
                     f20XY / f20X1Y1,
                     f01XY / f01X2Y2}};
}

void Rasterizer::RenderTriangle(const Triangle &triangle)
{
    Vector2i Min = {{std::numeric_limits<int>::max(),
                     std::numeric_limits<int>::max()}};
    Vector2i Max = {{-std::numeric_limits<int>::max(),
                     -std::numeric_limits<int>::max()}};
    Vector2i Clamp = {{resolution[0] - 1,
                       resolution[1] - 1}};

    float halfWidth = 0.5f * resolution[0];
    float halfHeight = 0.5f * resolution[1];
    std::array<Vector3f, 3> screenPoints = {
        Vector3f{{(triangle.getVertices()[0][0] + 1.f) * halfWidth, (triangle.getVertices()[0][1] + 1.f) * halfHeight, triangle.getVertices()[0][2]}},
        Vector3f{{(triangle.getVertices()[1][0] + 1.f) * halfWidth, (triangle.getVertices()[1][1] + 1.f) * halfHeight, triangle.getVertices()[1][2]}},
        Vector3f{{(triangle.getVertices()[2][0] + 1.f) * halfWidth, (triangle.getVertices()[2][1] + 1.f) * halfHeight, triangle.getVertices()[2][2]}}};

    Vector3i intPoints[] = {
        Vector3i{{(int)screenPoints[0][0], (int)screenPoints[0][1], (int)screenPoints[0][2]}},
        Vector3i{{(int)screenPoints[1][0], (int)screenPoints[1][1], (int)screenPoints[1][2]}},
        Vector3i{{(int)screenPoints[2][0], (int)screenPoints[2][1], (int)screenPoints[2][2]}}};

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            Min[j] = std::max(0, std::min(Min[j], intPoints[i][j]));
            Max[j] = std::min(Clamp[j], std::max(Max[j], intPoints[i][j]));
        }
    }

    int pointX, pointY;
    for (pointY = Min[1]; pointY <= Max[1]; ++pointY)
    {
        for (pointX = Min[0]; pointX <= Max[0]; ++pointX)
        {
            Vector3f bary = barycentric(screenPoints, pointX, pointY);


            if (bary[0] > 0 && bary[1] > 0 && bary[2] > 0)
            {
                int index = pointY * resolution[0] + pointX;

                float z = 0;
                for (int i = 0; i < 3; ++i)
                {
                    z += screenPoints[i][2] * bary[i];
                }

                if (index < 0 || index >= image.size())
                    continue;

                if (depth[index] < z)
                {
                    depth[index] = z;
                    ColorForProjectThree c{0.0f, 0.0f, 0.0f};
                    c += triangle.getColors()[0] * bary[0];
                    c += triangle.getColors()[1] * bary[1];
                    c += triangle.getColors()[2] * bary[2];

                    image[index] = c;
                }
            }
        }
    }
}

std::vector<ColorForProjectThree> Rasterizer::getPixels() const
{
    return image;
}

// Render Pipeline.
void Rasterizer::ProcessVertices(std::vector<Triangle> &triangles) const
{
    for (std::vector<Triangle>::iterator triangle = triangles.begin(); triangle != triangles.end(); ++triangle)
    {
        if(!fragment) {
            triangle->light(lights, eye);
        }
        triangle->transform(projection * camera);
    }
}

std::vector<Triangle> Rasterizer::ClipToPlane(const std::vector<Triangle> &triangles, const Plane &plane)
{
    std::vector<Triangle> result;
    result.reserve(triangles.size());
    for (std::vector<Triangle>::const_iterator triangle = triangles.begin(); triangle != triangles.end(); ++triangle)
    {
        std::vector<Triangle> clipped = plane.clipTriangle(*triangle);

        if (clipped.size() > 0)
        {
            std::copy(clipped.begin(), clipped.end(), std::back_inserter(result));
        }
    }
    return result;
}

std::vector<Triangle> Rasterizer::Clipping(const std::vector<Triangle> &triangles)
{
    std::vector<Triangle> clipped;
    clipped.reserve(triangles.size());
    std::copy(triangles.begin(), triangles.end(), std::back_inserter(clipped));
    for (int i = 0; i < 5; ++i)
    {
        clipped = ClipToPlane(clipped, frustum[i]);
    }
    return clipped;
}

void Rasterizer::RenderDepthMap(LightForProjectThree& light, const std::vector<Triangle>& triangles) {
    for (std::vector<Triangle>::const_iterator triangle = triangles.begin(); triangle != triangles.end(); ++triangle)
    {
        Vector2i Min = {{std::numeric_limits<int>::max(),
                         std::numeric_limits<int>::max()}};
        Vector2i Max = {{-std::numeric_limits<int>::max(),
                         -std::numeric_limits<int>::max()}};
        Vector2i Clamp = {{resolution[0] - 1,
                           resolution[1] - 1}};

        std::array<Vector3f, 3> verticies = triangle->getVertices();

        std::array<Vector3f, 3> screenPoints = {
            viewPort * (projection * (light.getMatrix() * verticies[0])),
            viewPort * (projection * (light.getMatrix() * verticies[1])),
            viewPort * (projection * (light.getMatrix() * verticies[2]))
        };

        Vector3i intPoints[] = {
            Vector3i{{(int)screenPoints[0][0], (int)screenPoints[0][1], (int)screenPoints[0][2]}},
            Vector3i{{(int)screenPoints[1][0], (int)screenPoints[1][1], (int)screenPoints[1][2]}},
            Vector3i{{(int)screenPoints[2][0], (int)screenPoints[2][1], (int)screenPoints[2][2]}}};

        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 2; ++j)
            {
                Min[j] = std::max(0, std::min(Min[j], intPoints[i][j]));
                Max[j] = std::min(Clamp[j], std::max(Max[j], intPoints[i][j]));
            }
        }

        int pointX, pointY;
        for (pointY = Min[1]; pointY <= Max[1]; ++pointY)
        {
            for (pointX = Min[0]; pointX <= Max[0]; ++pointX)
            {
                Vector3f bary = barycentric(screenPoints, pointX, pointY);


                if (bary[0] > 0 && bary[1] > 0 && bary[2] > 0)
                {
                    int index = pointY * resolution[0] + pointX;

                    float z = 0;
                    for (int i = 0; i < 3; ++i)
                    {
                        z += screenPoints[i][2] * bary[i];
                    }

                    Vector3f baryPoint = verticies[0] * bary[0] +
                                        verticies[1] * bary[1] +
                                        verticies[2] * bary[2];

                    light.setDepth(Vector3f{{(float) pointX, (float) pointY, z}});
                }
            }
        }
    }
}

void Rasterizer::Rasterize(const std::vector<Triangle> &triangles)
{

    for (std::vector<Triangle>::const_iterator triangle = triangles.begin(); triangle != triangles.end(); ++triangle)
    {
        Vector2i Min = {{std::numeric_limits<int>::max(),
                         std::numeric_limits<int>::max()}};
        Vector2i Max = {{-std::numeric_limits<int>::max(),
                         -std::numeric_limits<int>::max()}};
        Vector2i Clamp = {{resolution[0] - 1,
                           resolution[1] - 1}};

        std::array<Vector3f, 3> verticies = triangle->getVertices();

        std::array<Vector3f, 3> screenPoints = {
            viewPort * verticies[0],
            viewPort * verticies[1],
            viewPort * verticies[2]
        };

        Vector3i intPoints[] = {
            Vector3i{{(int)screenPoints[0][0], (int)screenPoints[0][1], (int)screenPoints[0][2]}},
            Vector3i{{(int)screenPoints[1][0], (int)screenPoints[1][1], (int)screenPoints[1][2]}},
            Vector3i{{(int)screenPoints[2][0], (int)screenPoints[2][1], (int)screenPoints[2][2]}}};

        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 2; ++j)
            {
                Min[j] = std::max(0, std::min(Min[j], intPoints[i][j]));
                Max[j] = std::min(Clamp[j], std::max(Max[j], intPoints[i][j]));
            }
        }

        int pointX, pointY;
        for (pointY = Min[1]; pointY <= Max[1]; ++pointY)
        {
            for (pointX = Min[0]; pointX <= Max[0]; ++pointX)
            {
                Vector3f bary = barycentric(screenPoints, pointX, pointY);

                // std::cout << "Bary: " << bary << std::endl;
                if (bary[0] > 0 && bary[1] > 0 && bary[2] > 0)
                {
                    int index = pointY * resolution[0] + pointX;

                    float z = 0;
                    for (int i = 0; i < 3; ++i)
                    {
                        z += screenPoints[i][2] * bary[i];
                    }

                    if (index < 0 || index >= image.size())
                        continue;


                    ColorForProjectThree fragment = ProcessFragment(index, *triangle, Vector3f{{(float)pointX, (float)pointY, z}}, bary);

                    Blending(index, z, fragment);
                }
            }
        }
    }
}

ColorForProjectThree Rasterizer::ProcessFragment(const unsigned int &index, const Triangle &triangle, const Vector3f &position, const Vector3f &bary)
{
    if(!fragment) {
        return (triangle.getColors()[0] * bary[0] + triangle.getColors()[1] * bary[1] + triangle.getColors()[2] * bary[2]);
    }

    float intensity = 1.f / sqrt(lights.size());
    ShadingForProjectThree shading = triangle.getShading();
    Matrix4 inverted = (projection * camera).Inverted();

    std::array<Vector3f, 3> verticies = {
        inverted * triangle.getVertices()[0],
        inverted * triangle.getVertices()[1],
        inverted * triangle.getVertices()[2],
    };

    Vector3f location = (verticies[0] * bary[0] + verticies[1] * bary[1] + verticies[2] * bary[2]);// * position[2];

    Vector3f normal = Vector3f::normalize(triangle.getNormals()[0] * bary[0] + triangle.getNormals()[1] * bary[1] + triangle.getNormals()[2] * bary[2]);

    ColorForProjectThree color{0,0,0};
    ColorForProjectThree min = shading.getColor() * .1f;
    
    for(int j = 0; j < lights.size(); ++j) {
        Vector3f lightDir = lights[j].getPosition() - location;
        float pointDepth = lightDir.magnitude();


        lightDir /= pointDepth;
        Vector3f direction = Vector3f::normalize(eye - location);
        
        // Generate the Half Vector
        Vector3f H = Vector3f::normalize(direction + lightDir);

        // Generate specular based on the surface normal and the light angle
        float diffuse = std::max(0.f, Vector3f::dot(normal, lightDir));
        float specular = pow(std::max(0.f, Vector3f::dot(normal, H)), shading.getShine());

        // Calculate the pixel color with the lights based on the formula provided
        color = {
            color[0] + (shading.getDiffuse() * shading.getColor()[0] * diffuse + shading.getSpecular() * specular) * intensity,
            color[1] + (shading.getDiffuse() * shading.getColor()[1] * diffuse + shading.getSpecular() * specular) * intensity,
            color[2] + (shading.getDiffuse() * shading.getColor()[2] * diffuse + shading.getSpecular() * specular) * intensity};
    }

    return ColorForProjectThree::clamp(color, min, ColorForProjectThree{1,1,1});
}

void Rasterizer::Blending(const unsigned int &index, const float &z, const ColorForProjectThree& fragment)
{
    if (depth[index] < z)
    {
        depth[index] = z;
        image[index] = fragment;
    }
}


std::vector<LightForProjectThree> Rasterizer::getLights() const {
    return lights;
}

void Rasterizer::SetLights(const std::vector<LightForProjectThree>& lights) {
    this->lights = lights;
}

void Rasterizer::SetCamera(const Matrix4 &matrix)
{
    camera = matrix;
    GenerateFrustum();
}

void Rasterizer::SetProjection(const Matrix4 &matrix)
{
    projection = matrix;
    GenerateFrustum();
}

void Rasterizer::SetViewPort(const Matrix4 &matrix)
{
    viewPort = matrix;
}

void Rasterizer::SetEye(const Vector3f& eye) {
    this->eye = eye;
}
void Rasterizer::SetFragment(const bool& useFrag) {
    fragment = useFrag;
}

void Rasterizer::GenerateFrustum()
{
    Matrix4 invPro = projection.Inverted();
    frustum[0] = Plane(invPro * Vector3f{{0, -1, 0}}, -2);
    frustum[1] = Plane(invPro * Vector3f{{0, 1, 0}}, -2);
    frustum[2] = Plane(invPro * Vector3f{{0, 0, -1}}, -2);
    frustum[3] = Plane(invPro * Vector3f{{-1, 0, 0}}, -2);
    frustum[4] = Plane(invPro * Vector3f{{1, 0, 0}}, -2);
}
