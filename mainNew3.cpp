// Computer Graphics Project Assignment 3 Rasterization Rendering Pipeline
// mainNew3.cpp
#include "Math/Matrix4.h"
#include "Geometry/PolygonForProjectThree.h"
#include "Geometry/Triangle.h"
#include "PpmFileForProjectThree.h"
#include "Rasterizer.h"
#include "NffParserForProjectThree.h"
#include <algorithm>
#include <vector>

int main(int argc, char **argv)
{
    NffParserForProjectThree scene;

    scene.parse(argv[1]);

    PpmFileForProjectThree output;

    ViewPortForProjectThree view = scene.getViewPort();

    std::vector<Renderable *> objects = scene.getObjects();
    Rasterizer rasterizer(view.getResolution(), scene.getBackgroundColor());
    Matrix4 viewPort = Matrix4::ViewPortForProjectThree(view.getResolution());
    Matrix4 projection = Matrix4::Projection({{1.f, 10.f}}, view.getAngle(), view.getAspectRatio());

    // Convert the world points into camera points.
    Matrix4 camera = Matrix4::LookAt(view.getFrom(), view.getAt(), view.getUp());

    std::vector<LightForProjectThree *> lights = scene.getLights();
    std::vector<Vector3f> transformedLights(lights.size());
    for(int i = 0; i < lights.size(); ++i) {
        transformedLights.push_back(camera * lights[i]->getPosition());
    }

    float lightIntensity = 1/sqrt(lights.size());

    for (std::vector<Renderable *>::iterator iter = objects.begin(); iter != objects.end(); ++iter)
    {
        std::vector<Triangle> triangles = (*iter)->getTriangles();

        for (int i = 0; i < triangles.size(); ++i)
        {
            std::array<Vector3f, 3> rawVertices = triangles[i].getVertices();
            std::array<Vector3f, 3> rawNormals = triangles[i].getNormals();
            Vector3f transformed[3] = {
                camera * rawVertices[0],
                camera * rawVertices[1],
                camera * rawVertices[2],
            };
            Vector3f transformedNormals[3] = {
                camera.getRotation() * rawNormals[0],
                camera.getRotation() * rawNormals[1],
                camera.getRotation() * rawNormals[2],
            };

            Vector3f normal = Vector3f::normalize(
                Vector3f::cross(
                    transformed[2] - transformed[0],
                    transformed[1] - transformed[0]
                )
            );

            if(Vector3f::dot(normal, (transformed[0] - camera.getTranslation())) > 0)
	    {
		continue;
	    }

            ColorForProjectThree colors[3];
            ColorForProjectThree min = triangles[i].getShading().getColor() * .1f;

            for(int j = 0; j < 3; ++j) {
                for(int k = 0; k < lights.size(); ++k) {
                    float intensity = lightIntensity * Vector3f::dot(transformedNormals[j], Vector3f::normalize(transformedLights[k] - transformed[j]));
                    colors[j] += triangles[i].getShading().getColor() * intensity;
                }

                colors[j] = ColorForProjectThree::clamp(colors[j], min, ColorForProjectThree{1, 1, 1});

                transformed[j] = projection * transformed[j];
            }

            for(int j = 0; j < 3; ++j) {
                transformed[j][0] += 1.f;
                transformed[j][1] += 1.f;
                transformed[j][0] *= 0.5f * view.getResolution()[0];
                transformed[j][1] *= 0.5f * view.getResolution()[1];
            }

            rasterizer.RenderTriangle(transformed, colors);
        }
    }

    output.write("output.ppm", {{512, 512}}, rasterizer.getPixels());

    return 0;
}
