// Computer Graphics Project Assignment 3 Rasterization Rendering Pipeline
// ViewPortForProjectThree.h
#ifndef VIEWPORTFORPROJECTTHREE_H
#define VIEWPORTFORPROJECTTHREE_H

#include "../Math/Vector.h"

struct ViewPortForProjectThree
{
public:
    ViewPortForProjectThree();

    Vector3f getFrom() const;
    Vector3f getAt() const;
    Vector3f getUp() const;
    float getAspectRatio() const;
    float getAngle() const;
    float getAngleScaled() const;
    float getHither() const;
    float getDepthField() const;
    float inverseWidth() const;
    float inverseHeight() const;
    int getResolutionSize() const;
    Vector2i getResolution() const;

    friend std::istream& operator>> (std::istream&, ViewPortForProjectThree&);

private:
    Vector3f from;
    Vector3f at;
    Vector3f up;
    float aspectRatio;
    float angle;
    float angleScale;
    float hither;
    float depthField;
    float invWidth;
    float invHeight;
    int resolutionSize;
    Vector2i resolution;
};

#endif

