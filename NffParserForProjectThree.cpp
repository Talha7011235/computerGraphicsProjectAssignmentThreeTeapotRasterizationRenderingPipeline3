// Computer Graphics Project Assignment 3 Rasterization Rendering Pipeline
// NffParserForProjectThreeForProjectThreeForProjectThree.cpp
#include "NffParserForProjectThree.h"
#include "Geometry/PolygonForProjectThree.h"
#include <fstream>

NffParserForProjectThree::NffParserForProjectThree()
	: backgroundColor(), isPhong(false),aperature(0), objects(), lights()
{}

// Ensure that the created elements inside the objects vector get deleted to prevent a memory leak.
NffParserForProjectThree::~NffParserForProjectThree()
{
	for(std::vector<Renderable*>::iterator iter = objects.begin(); iter != objects.end(); ++iter)
	{
		delete(*iter);
	}
	objects.clear();
	lights.clear();
}

bool NffParserForProjectThree::isPhongRendering() const {
	return isPhong;
}
float NffParserForProjectThree::getAperatureSize() const {
	return aperature;
}
int NffParserForProjectThree::getSampleSize() const {
	return samples;
}
void NffParserForProjectThree::setPhongShading(const bool& value) {
	isPhong = value;
}
void NffParserForProjectThree::setAperatureSize(const float& value) {
	aperature = value;
}
void NffParserForProjectThree::setSampleSize(const int& value) {
	samples = value;
}

ColorForProjectThree& NffParserForProjectThree::getBackgroundColor()
{
	return backgroundColor;
}

ViewPortForProjectThree& NffParserForProjectThree::getViewPort()
{
	return viewPort;
}

std::vector<Renderable*>& NffParserForProjectThree::getObjects()
{
	return objects;
}
std::vector<LightForProjectThree>& NffParserForProjectThree::getLights()
{
	return lights;
}

void NffParserForProjectThree::parse(const std::string& fileName)
{
	std::ifstream file(fileName);
	if(!file.good())
	{
		throw std:: runtime_error("Error: Unable to open Neutral File Format NFF file, that is .nff File, for reading.");
	}

	ShadingForProjectThree current = { {0,0,0}, 0,0,0,0,0};

	// Do a while loop() to loop through the lines until reaching the end.
	while(!file.eof())
	{
		// Reset the Element represented by the Character Variable "char element" to 0 so that an input is not represented.
		char element = 0;
		file >> element;
		switch (element)
		{
		// Fill the background color with the specified values.
		case 'b':
		    file >> backgroundColor;
		    break;

		// Viewpoint.
		case 'v':
		    file >> viewPort;
		    break;

		// Fill Shading.
		case 'f':
		    file >> current;
		    break;

		// Polygon.
		case 'p':
		{
		    PolygonForProjectThree *p = new PolygonForProjectThree();
		    file >> *p;
		    p->setShading(current);
		    objects.push_back(p);
		    break;
		}

		// Light.
		case 'l':
		{
			LightForProjectThree light;
			file >> light;
			lights.push_back(light);
			break;
		}
		// Skip current line when the current line cannot recognize a element to parse.
		default:
		    file.ignore(255, '\n');
		    break;
		}
	}

	file.close();
}

