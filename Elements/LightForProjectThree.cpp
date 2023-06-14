// Computer Graphics Project Assignment 3 Rasterization Rendering Pipeline
// LightForProjectThree.cpp
#include "LightForProjectThree.h"
#include <limits>

LightForProjectThree::LightForProjectThree() : position() {}
LightForProjectThree:: LightForProjectThree(const Vector3f& p) : position(p) {}

Vector3f LightForProjectThree::getPosition() const {
    return position;
}

Matrix4 LightForProjectThree::getMatrix() const {
	return lightView;
}
float LightForProjectThree::getDepth(const Vector3f& point) const {
	// Transform the point to the view of the light.
	Vector3f shadowPoint = lightVP * (lightProj * (lightView * point));

	// See if it is in the light's buffer.
	const int index = (int)shadowPoint[1] * resolution[0] + (int)shadowPoint[0];

	if(index >=0 && index < (resolution[0] * resolution[1])) {
		// If it is in the light's buffer, then return the depth.
		return buffer[index];
	}

	// Otherwise, return the max.
	return std::numeric_limits<float>::max();
}

std::vector<ColorForProjectThree> LightForProjectThree::getPixels() const {
	std::vector<ColorForProjectThree> pixels;
	pixels.reserve(buffer.size());
	float Max = -std::numeric_limits<float>::max();
	float Min = std::numeric_limits<float>::max();

	for(std::vector<float>::const_iterator iter = buffer.begin(); iter < buffer.end(); ++iter) {
		if((*iter) < std::numeric_limits<float>::max()) {
			Max = std::max(Max, (*iter));
		}
		Min = std::min(Min, (*iter));
	}

	float range = (Max - Min);
	for(std::vector<float>::const_iterator iter = buffer.begin(); iter < buffer.end(); ++iter) {
		pixels.push_back(ColorForProjectThree{
			((*iter) / range) - Min,
			((*iter) / range) - Min,
			((*iter) / range) - Min,
		});
	}

	return pixels;
}

Vector3f LightForProjectThree::transformPoint(const Vector3f& point) const {
	return lightVP * (lightProj * (lightView * point));
}

void LightForProjectThree::setResolution(const Vector2i& resolution) {
	this->resolution = resolution;

	buffer.clear();
    buffer.resize(resolution[0] * resolution[1]);
    std::fill(buffer.begin(), buffer.end(), std::numeric_limits<float>::max());
}

void LightForProjectThree::setMatrix(const Matrix4& lookAt, const Matrix4& projection, const Matrix4& viewPort) {
	lightView = lookAt;
	lightProj = projection;
	lightVP = viewPort;
}


bool LightForProjectThree::isInShadow(const Vector3f& point) const {
	Vector3f shadowPoint = lightVP * (lightProj * (lightView * point));

	const int index = (int)shadowPoint[1] * resolution[0] + (int)shadowPoint[0];

	if(index >=0 && index < (resolution[0] * resolution[1])) {
		// In terms of this if statement, return the Depth.
		return buffer[index] > shadowPoint[2];
	}
	return false;
}

void LightForProjectThree::setDepth(const Vector3f& point) {

	const int index = (int)point[1] * resolution[0] + (int)point[0];
	if(index >=0 && index < (resolution[0] * resolution[1])) {
		if(buffer[index] == std::numeric_limits<float>::max() || buffer[index] < point[2]) {
			buffer[index] = point[2];
		}
	}
}

std::istream& operator>> (std::istream& in, LightForProjectThree& value)
{
	in >> value.position;
	return in;
}

std::ostream& operator << (std::ostream& out, const LightForProjectThree& value) {
	out << "Light at: " << value.position;
	return out;
}
