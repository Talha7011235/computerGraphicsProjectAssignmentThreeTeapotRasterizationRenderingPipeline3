// Computer Graphics Project Assignment 3 Rasterization Rendering Pipeline
// Triangle.cpp
#include "Triangle.h"

Triangle::Triangle(const std::array<Vector3f, 3>& v, const std::array<Vector3f, 3>& n, const ShadingForProjectThree& s) : vertices(v), normals(n), shading(s) {}
Triangle::Triangle(const std::array<Vector3f, 3>& v, const std::array<Vector3f, 3>& n, const ShadingForProjectThree& s, const std::array<ColorForProjectThree, 3>& c) : vertices(v), normals(n), shading(s), colors(c) {}
Triangle::~Triangle() {}

std::array<Vector3f, 3> Triangle::getVertices() const {
    return vertices;
}

std::array<Vector3f, 3> Triangle::getNormals() const {
    return normals;
}

std::array<ColorForProjectThree, 3> Triangle::getColors() const {
    return colors;
}

ShadingForProjectThree Triangle::getShading() const {
    return shading;
}

std::array<std::vector<Vector3f>, 3> Triangle::getLightDirections() const {
    return lightDirections;
}

void Triangle::setColors(const std::array<ColorForProjectThree, 3>& colors) {
    this->colors = colors;
}

void Triangle::light(const std::vector<LightForProjectThree>& lights, const Vector3f& camera) {
    float intensity = 1.f/sqrt(lights.size());
    ColorForProjectThree min = shading.getColor() * .1f;
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < lights.size(); ++j) {
            Vector3f lightDir = Vector3f::normalize(lights[j].getPosition() - vertices[i]);
            Vector3f direction = Vector3f::normalize(camera - vertices[i]);

            // Generate half vector
            Vector3f H = Vector3f::normalize(direction + lightDir);
            // Generate diffuse and specular based on the surface normal and the light angle
            float diffuse = std::max(0.f, Vector3f::dot(normals[i], lightDir));
            float specular = pow(std::max(0.f, Vector3f::dot(normals[i], H)), shading.getShine());

            // Calculate the pixel color with the lights based on the formula provided
            colors[i] = {
                colors[i][0] + ((shading.getDiffuse() * shading.getColor()[0] * diffuse + specular * shading.getSpecular()) * intensity),
                colors[i][1] + ((shading.getDiffuse() * shading.getColor()[1] * diffuse + specular * shading.getSpecular()) * intensity),
                colors[i][2] + ((shading.getDiffuse() * shading.getColor()[2] * diffuse + specular * shading.getSpecular()) * intensity)};
        }
        colors[i] = ColorForProjectThree::clamp(colors[i] + min, min, ColorForProjectThree::one());
    }
}

void Triangle::transform(const Matrix4& matrix) {
    for(int i = 0; i < 3; ++i) {
        vertices[i] = matrix * vertices[i];
    }
}
