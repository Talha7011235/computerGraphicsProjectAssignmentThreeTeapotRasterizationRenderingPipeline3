// Computer Graphics Project Assignment 3 Rasterization Rendering Pipeline
// PpmFileForProjectThree.cpp
#include "PpmFileForProjectThree.h"
#include <fstream>
#include <vector>

void PpmFileForProjectThree::write(const std::string fileName, Vector2i resolution, const std::vector<ColorForProjectThree> pixels)
{
	std::ofstream output(fileName, std::ofstream::out | std::ofstream::binary);
	if (!output.good())
	{
		throw std::runtime_error("Error: Not able to create/open Image File for saving.");
	}

	// Follow the Portable Pixel Map PPM Version 6 P6 header to indicate that the version is binary instead of the American Standard Code for Information
	// Interchange ASCII version.
	output << "P6" << std::endl;
	output << resolution[0] << " " << resolution[1] << std::endl;
	output << "255" << std::endl;

	// Loop through the Pixels and Output.
	for (std::vector<ColorForProjectThree>::const_iterator iter = pixels.begin(); iter != pixels.end(); ++iter)
	{
		std::array<unsigned char, 3> values = iter->asByteArray();
		output << values[0] << values[1] << values[2];
	}

	output.close();
}


