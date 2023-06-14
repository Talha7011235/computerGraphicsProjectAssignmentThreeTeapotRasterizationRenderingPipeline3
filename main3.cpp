// Computer Graphics Project Assignment 3 Rasterization Rendering Pipeline
// main3.cpp 
#include "Math/Matrix4.h"
#include "Geometry/Plane.h"
#include "Geometry/PolygonForProjectThree.h"
#include "Geometry/Triangle.h"
#include "PpmFileForProjectThree.h"
#include "Rasterizer.h"
#include "NffParserForProjectThree.h"
#include <algorithm>
#include <vector>
#include <cstring>

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "Rasterize" << std::endl;
		std::cout << "Usage: " << argv[0] << " [-f] filename [output]" << std::endl;
		return 1;
	}
    NffParserForProjectThree scene;
	bool fragment = false;
	int state = 0;
	std::string filename("");
	std::string outputFilename("output.ppm");

    for(int i = 1; i < argc; ++i) {

		// Check if the Phong Shading is requested.
		if(strcmp(argv[i], "-f") == 0) {
			fragment = true;
			continue;
		}

		if(state == 0) {
			filename = argv[i];
			++state;
			continue;
		}
		if(state == 1) {
			outputFilename = argv[i];
			++state;
			continue;
		}
	}

    scene.parse(filename);

    ViewPortForProjectThree view = scene.getViewPort();

    std::vector<Renderable*> objects = scene.getObjects();
    std::vector<LightForProjectThree> lights = scene.getLights();

    Rasterizer rasterizer(view.getResolution(), scene.getBackgroundColor());

    Matrix4 viewPort = Matrix4::ViewPortForProjectThree(view.getResolution());
    Matrix4 projection = Matrix4::Projection({{-0.5f, -10.f}}, view.getAngle(), view.getAspectRatio());
    Matrix4 camera = Matrix4::LookAt(view.getFrom(), view.getAt(), view.getUp());

    rasterizer.SetFragment(fragment);
    rasterizer.SetCamera(camera);
    rasterizer.SetProjection(projection);
    rasterizer.SetViewPort(viewPort);
    rasterizer.SetEye(view.getFrom());

    rasterizer.SetLights(lights);

    int size = objects.size();
    int counter = 0;
    counter = 0;
    std::cout << "Rendering Image" << std::endl;
    for (std::vector<Renderable*>::iterator iter = objects.begin(); iter != objects.end(); ++iter)
    {
        std::vector<Triangle> triangles = (*iter)->getTriangles();

        rasterizer.ProcessVertices(triangles);

        triangles = rasterizer.Clipping(triangles);

        rasterizer.Rasterize(triangles);

        std::cout << ++counter << "/" << size << " (" << ((counter * 100) / size) << "%)" << std::endl << "\x1b[A";
    }

    PpmFileForProjectThree::write(outputFilename, view.getResolution(), rasterizer.getPixels());

    return 0;
}
