// Computer Graphics Project Assignment 3 Rasterization Rendering Pipeline
// Plane.cpp
#include "Plane.h"

Plane::Plane() : normal(), distance(0) {}
Plane::Plane(const Vector4f& vec) {
    distance = vec[3];
    normal = Vector3f{{
        vec[0],
        vec[1],
        vec[2]
    }};

    float mag = normal.magnitude();
    distance /= mag;
    normal /= mag;
}
Plane::Plane(const Vector3f &n, const float &d) : normal(n), distance(d) {}
Plane::~Plane() {}

Vector3f Plane::intersection(const Vector3f &a, const Vector3f &b) const
{
    // Intersection on plane
    float aDistance = Vector3f::dot(a, normal) - distance;
    Vector3f direction = Vector3f::normalize(b - a);
    float t = -aDistance / Vector3f::dot(normal, direction);

    return a + t * direction;
}

void Plane::transform(const Matrix4& matrix) {
    normal = matrix.getRotation() * normal;
    distance -= Vector3f::dot(normal, matrix.getTranslation());
}

std::vector<Triangle> Plane::clipTriangle(const Triangle &triangle) const
{
    // F(p) = n * (p-q) = 0
    // F(p) = n * p + d = 0
    // p = a+t(b-a)
    // n *(a+t(b-a))+d = 0
    // t = (n*a+d) / (n*(a-b))
    std::array<Vector3f, 3> vertices = triangle.getVertices();
    std::vector<Triangle> triangles;
    std::array<float, 3> distances;

    int insideCount = 0;
    int outsideCount = 0;
    for (int i = 0; i < 3; ++i)
    {
        distances[i] = Vector3f::dot(vertices[i], normal) - distance;
    }

    if (distances[0] >= 0 && distances[1] >= 0 && distances[2] >= 0)
    {
        triangles.push_back(triangle);
        return triangles;
    }
    if (distances[0] <= 0 && distances[1] <= 0 && distances[2] <= 0)
    {
        return triangles;
    }

    std::array<Vector3f, 3> normals = triangle.getNormals();
    std::array<ColorForProjectThree, 3> colors = triangle.getColors();
    std::array<float, 3> distanceTotals;
    distanceTotals[0] = (vertices[1] - vertices[0]).magnitude();
    distanceTotals[1] = (vertices[2] - vertices[1]).magnitude();
    distanceTotals[2] = (vertices[0] - vertices[2]).magnitude();

    int prevI = 2;
    for (int i = 0; i < 3; ++i)
    {
        int nextI = (i + 1) % 3;
        if (distances[i] > 0 && distances[nextI] <= 0 && distances[prevI] <= 0)
        { // Only A is positive
            Vector3f ab = intersection(vertices[i], vertices[nextI]);
            Vector3f ac = intersection(vertices[i], vertices[prevI]);

            float abDistance = (ab - vertices[i]).magnitude() / distanceTotals[i];
            float acDistance = (ac - vertices[i]).magnitude() / distanceTotals[prevI];
	    // Use the lerp() Function to determine the lerped normal.
            Vector3f normalAB = Vector3f::normalize(Vector3f::lerp(normals[nextI], normals[i], abDistance));
	    // Use the lerp() Function to determine the lerped normal.
            Vector3f normalAC = Vector3f::normalize(Vector3f::lerp(normals[prevI], normals[i], acDistance));

            // Use the lerp() Function to lerp the Color.
            ColorForProjectThree abColor = ColorForProjectThree::lerp(colors[i], colors[nextI], abDistance);
            ColorForProjectThree acColor = ColorForProjectThree::lerp(colors[i], colors[prevI], acDistance);

            triangles.push_back(
                Triangle{
                    std::array<Vector3f, 3>{{vertices[i], ab, ac}},
                    std::array<Vector3f, 3>{{triangle.getNormals()[i], normalAB, normalAC}},
                    triangle.getShading(),
                    {colors[i], abColor, acColor}
                });
            return triangles;
        }
        if (distances[i] < 0 && distances[nextI] >= 0 && distances[prevI] >= 0)
        { // Only A is negative
            Vector3f ab = intersection(vertices[i], vertices[nextI]);
            Vector3f ac = intersection(vertices[i], vertices[prevI]);

            float abDistance = (ab - vertices[i]).magnitude() / distanceTotals[i];
            float acDistance = (ac - vertices[i]).magnitude() / distanceTotals[prevI];
	    // Use the lerp() Function to determine the lerped normal.
            Vector3f normalAB = Vector3f::normalize(Vector3f::lerp(normals[nextI], normals[i], abDistance));
	    // Use the lerp() Function to determine the lerped normal.
            Vector3f normalAC = Vector3f::normalize(Vector3f::lerp(normals[prevI], normals[i], acDistance));

            // Use the lerp() Function to lerp the Color.
            ColorForProjectThree abColor = ColorForProjectThree::lerp(colors[i], colors[nextI], abDistance);
            ColorForProjectThree acColor = ColorForProjectThree::lerp(colors[i], colors[prevI], acDistance);

            triangles.push_back(
                Triangle{
                    std::array<Vector3f, 3>{{ab, vertices[nextI], vertices[prevI]}},
                    std::array<Vector3f, 3>{{normalAB, triangle.getNormals()[nextI], triangle.getNormals()[prevI]}},
                    triangle.getShading(),
                    {abColor, colors[nextI], colors[prevI]}
                });

            triangles.push_back(
                Triangle{
                    std::array<Vector3f, 3>{{ac, ab, vertices[prevI]}},
                    std::array<Vector3f, 3>{{normalAC, normalAB, triangle.getNormals()[prevI]}},
                    triangle.getShading(),
                    {acColor, abColor, colors[prevI]}
                });
            return triangles;
        }
        prevI = i;
    }
    return triangles;
}

std::ostream& operator<< (std::ostream& out, const Plane& plane) {
    out << "(" << plane.normal << ") " << plane.distance;
    return out;
}
