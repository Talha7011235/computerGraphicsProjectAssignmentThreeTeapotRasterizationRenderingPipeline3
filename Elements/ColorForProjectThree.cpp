// Computer Graphics Project Assignment 3 Rasterization Rendering Pipeline
// ColorForProjectThree.cpp
#include "ColorForProjectThree.h"
#include <algorithm>
#include <sstream>

ColorForProjectThree::ColorForProjectThree() : Vector3f() {}
ColorForProjectThree::ColorForProjectThree(const Vector3f& copy) : Vector3f(copy) {}
ColorForProjectThree::ColorForProjectThree(const float& x, const float& y, const float& z) : Vector3f{{x, y, z}} {}
ColorForProjectThree::~ColorForProjectThree() {}

std::array<unsigned char, 3> ColorForProjectThree::asByteArray() const {
	return {
		(unsigned char)(data[0] * 255),
		(unsigned char)(data[1] * 255),
		(unsigned char)(data[2] * 255)
	};
}
