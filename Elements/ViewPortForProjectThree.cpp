// Computer Graphics Project Assignment 3 Rasterization Rendering Pipeline
// ViewPortForProjectThree.cpp

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include "ViewPortForProjectThree.h"
#include <cmath>

ViewPortForProjectThree::ViewPortForProjectThree() : from{{0, 0, 0}}, at{{0, 0, 1}}, up{{0, 1, 0}}, angle(45), hither(0.1f), resolution{{512, 512}} {
	depthField = (at - from).magnitude();
}

Vector3f ViewPortForProjectThree::getFrom() const
{
	return from;
}

Vector3f ViewPortForProjectThree::getAt() const
{
	return at;
}

Vector3f ViewPortForProjectThree::getUp() const
{
	return up;
}

float ViewPortForProjectThree::getAspectRatio() const
{
	return aspectRatio;
}

float ViewPortForProjectThree::getAngle() const
{
	return angle;
}

float ViewPortForProjectThree::getAngleScaled() const {
	return angleScale;
}

float ViewPortForProjectThree::getHither() const
{
	return hither;
}

float ViewPortForProjectThree::getDepthField() const {
	return depthField;
}

float ViewPortForProjectThree::inverseWidth() const {
	return invWidth;
}

float ViewPortForProjectThree::inverseHeight() const {
	return invHeight;
}

int ViewPortForProjectThree::getResolutionSize() const {
	return resolutionSize;
}

Vector2i ViewPortForProjectThree::getResolution() const
{
	return resolution;
}

std::istream& operator>> (std::istream& in, ViewPortForProjectThree& value)
{
	std::string ignore;
	in >> ignore >> value.from;
	in >> ignore >> value.at;
	in >> ignore >> value.up;
	in >> ignore >> value.angle;
	in >> ignore >> value.hither;
	in >> ignore >> value.resolution;
	value.depthField = (value.at - value.from).magnitude();

	float radians = (value.angle * 0.5) * M_PI / 180;
	value.angleScale = tan(radians);

	value.invWidth = 1.f / value.resolution[0];
	value.invHeight = 1.f / value.resolution[1];
	value.resolutionSize = value.resolution[0] * value.resolution[1];
	value.aspectRatio = value.resolution[0] / value.resolution[1];
	return in;
}

