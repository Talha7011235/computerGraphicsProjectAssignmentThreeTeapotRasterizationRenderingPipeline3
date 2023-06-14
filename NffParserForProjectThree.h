// Computer Graphics Project Assignment 3 Rasterization Rendering Pipeline
// NffParserForProjectThree.h
#ifndef NFFPARSERFORPROJECTTHREE_H
#define NFFPARSERFORPROJECTTHREE_H

#include "Elements/ColorForProjectThree.h"
#include "Elements/ViewPortForProjectThree.h"
#include "Elements/LightForProjectThree.h"
#include "Geometry/Renderable.h"
#include <string>
#include <vector>

// Parses the Neutral File Format NFF File and holds some minor settings. If more settings are needed, then split into parser and settings classes.
class NffParserForProjectThree
{
public:
    NffParserForProjectThree();
    ~NffParserForProjectThree();

    bool isPhongRendering() const;
    float getAperatureSize() const;
    int getSampleSize() const;
    ColorForProjectThree& getBackgroundColor();
    ViewPortForProjectThree& getViewPort();
    std::vector<Renderable*>& getObjects();
    std::vector<LightForProjectThree>& getLights();

    void setPhongShading(const bool&);
    void setAperatureSize(const float&);
    void setSampleSize(const int&);

    void parse(const std::string&);

private:
    bool isPhong;
    float aperature;
    int samples;
    ColorForProjectThree backgroundColor;
    ViewPortForProjectThree viewPort;
    std::vector<Renderable*> objects;
    std::vector<LightForProjectThree> lights;
};

#endif

