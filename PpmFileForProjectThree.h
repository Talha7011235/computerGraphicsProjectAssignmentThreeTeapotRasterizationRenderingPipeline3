// Computer Graphics Project Assignment 3 Rasterization Rendering Pipeline
// PpmFileForProjectThree.h
#ifndef PPMFILE_H
#define PPMFILE_H

#include "Math/Vector.h"
#include "Elements/ColorForProjectThree.h"
#include <string>
#include <vector>

class PpmFileForProjectThree
{
public:
    static void write(const std::string fileName, Vector2i resolution, std::vector<ColorForProjectThree> pixels);
};

#endif

