// Computer Graphics Project Assignment 3 Rasterization Rendering Pipeline
// ShadingForProjectThree.cpp
#include "ShadingForProjectThree.h"

ShadingForProjectThree::ShadingForProjectThree() : color(), diffuse(0), specular(0), shine(0), transmittance(0), indexOfRefraction(0) {}
ShadingForProjectThree::ShadingForProjectThree(ColorForProjectThree cForColor, float dForDiffuse, float sForSpecular, float shForShine, float tForTransmittance, float iForIndexOfRefraction) : color(cForColor), diffuse(dForDiffuse), specular(sForSpecular), shine(shForShine), transmittance(tForTransmittance), indexOfRefraction(iForIndexOfRefraction) {}

ColorForProjectThree ShadingForProjectThree::getColor()
{
	return color;
}

float ShadingForProjectThree::getDiffuse()
{
	return diffuse;
}

float ShadingForProjectThree::getSpecular()
{
	return specular;
}

float ShadingForProjectThree::getShine()
{
	return shine;
}

float ShadingForProjectThree::getTransmittance()
{
	return transmittance;
}

float ShadingForProjectThree::getIndexOfRefraction()
{
	return indexOfRefraction;
}

std::istream& operator>> (std::istream& in, ShadingForProjectThree& value)
{
	in >> value.color >> value.diffuse >> value.specular >> value.shine >> value.transmittance >> value.indexOfRefraction;
	return in;
}

