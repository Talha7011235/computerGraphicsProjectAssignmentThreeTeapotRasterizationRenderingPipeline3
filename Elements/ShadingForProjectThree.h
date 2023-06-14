// Computer Graphics Project Assignment 3 Rasterization Rendering Pipeline
// ShadingForProjectThree.h
#ifndef SHADINGFORPROJECTTHREE_H
#define SHADINGFORPROJECTTHREE_H

#include "ColorForProjectThree.h"

struct ShadingForProjectThree
{
public:
    ShadingForProjectThree();
    ShadingForProjectThree(ColorForProjectThree, float, float, float, float, float);

    ColorForProjectThree getColor();
    float getDiffuse();
    float getSpecular();
    float getShine();
    float getTransmittance();
    float getIndexOfRefraction();

    friend std::istream& operator>> (std::istream&, ShadingForProjectThree&);

private:
    ColorForProjectThree color;
    float diffuse;
    float specular;
    float shine;
    float transmittance;
    float indexOfRefraction;
};

#endif

