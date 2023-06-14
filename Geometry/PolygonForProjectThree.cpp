// Computer Graphics Project Assignment 3 Rasterization Rendering Pipeline
// PolygonForProjectThree.cpp
#define _USE_MATH_DEFINES

#include "PolygonForProjectThree.h"
#include <algorithm>
#include <iostream>
#include <limits>
#include <cmath>

PolygonForProjectThree::PolygonForProjectThree() : count(0), verticies(), normals(), indicies(), shading() {}

PolygonForProjectThree::~PolygonForProjectThree()
{
	indicies.clear();
	verticies.clear();
	normals.clear();
}

int PolygonForProjectThree::getCount() const
{
	return count;
}

int PolygonForProjectThree::getType() const {
	return 0;
}

std::vector<Vector3f> PolygonForProjectThree::getVerticies() const
{
	return verticies;
}

std::vector<Vector3f> PolygonForProjectThree::getNormals() const
{
	return normals;
}

std::vector<Triangle> PolygonForProjectThree::getTriangles() const {
	std::vector<Triangle> faces;
	faces.reserve(indicies.size() / 3);
	for(int i = 0; i < indicies.size(); i += 3) {
		faces.push_back(
			{
				{verticies[indicies[i]], verticies[indicies[i+1]], verticies[indicies[i+2]]},
				{normals[indicies[i]], normals[indicies[i+1]], normals[indicies[i+2]]},
				shading
			});
	}
	return faces;
}

void PolygonForProjectThree::setShading(ShadingForProjectThree sIsForShading)
{
	shading = sIsForShading;
}

std::istream& operator>> (std::istream& in, PolygonForProjectThree& value)
{
	char p = in.peek();
	bool isPatch = false;
	if(p == 'p')
	{
		in >> p;
		isPatch = true;
	}

	in >> value.count;

	value.verticies.reserve(value.count);

	Vector3f vertex;
	Vector3f normal;
	for(int iIndex = 0; iIndex < value.count; ++iIndex)
	{
		in >> vertex;
		value.verticies.push_back(vertex);

		if(isPatch) {
			in >> normal;
			value.normals.push_back(normal);
		}
	}

	if(!isPatch) {
		normal = Vector3f::normalize(
			Vector3f::cross(
				value.verticies[1] - value.verticies[0],
				value.verticies[2] - value.verticies[0]
			)
		);

		while(value.normals.size() < value.verticies.size()) {
			value.normals.push_back(normal);
		}
	}

	// Triangulate the verticies.
	if (value.verticies.size() == 3)
	{
		// If it is the case of working with a Triangle, then there is no need to triangulate.
		value.indicies.push_back(0);
		value.indicies.push_back(1);
		value.indicies.push_back(2);
	}
	else
	{
		// Otherwise, there are more than three verticies.
		std::vector<float> angles;

		// Determine the initial angles.
		int a = value.count - 1;
		for (int iIndex = 0; iIndex < value.count; ++iIndex)
		{
			Vector3f AC = Vector3f::normalize(value.verticies[a] - value.verticies[iIndex]);
			Vector3f AB = Vector3f::normalize(value.verticies[(iIndex + 1) % value.count] - value.verticies[iIndex]);
			angles.push_back(AC.getAngle(AB));
			a = iIndex;
		}

		// Do Triangulation based off of the angles. In order to triangulate effectively, select the smallest angle.
		for (int iIndex = 0; iIndex < value.count - 2; ++iIndex)
		{
			// Find the smallest angle.
			int smallest = 0;
			float smallestAngle = angles[0];
			for(int jIndex = 0; jIndex < value.count; ++jIndex)
			{
				if (angles[jIndex] < angles[smallest])
				{
					smallest = jIndex;
					smallestAngle = angles[jIndex];
				}
			}

			// Determine the verticies based on the initial triangle.
			int vertexOne = smallest; // 0

			// Create connected verticies to ensure the avoidance of using any vertex that has already been removed from the angle set.
			int vertexTwo = (smallest + 1) % value.count; // 1
			while (angles[vertexTwo] == std::numeric_limits<float>::max())
			{
				vertexTwo = (vertexTwo + 1) % value.count;
			}

			int vertexThree = (smallest + value.count - 1) % value.count; // 5
			while (angles[vertexThree] == std::numeric_limits<float>::max())
			{
				vertexThree = (vertexThree + value.count - 1) % value.count;
			}

			// Add Triangle to indicies.
			value.indicies.push_back(vertexOne);
			value.indicies.push_back(vertexTwo);
			value.indicies.push_back(vertexThree);

			// Update angle at Vertex 2 that is represented by the Integer Variable "int vertexTwo".
			Vector3f vertexTwoa = Vector3f::normalize(value.verticies[vertexThree] - value.verticies[vertexTwo]);
			Vector3f vertexTwob = Vector3f::normalize(value.verticies[(vertexTwo + 1) % value.count] - value.verticies[vertexTwo]);
			angles[vertexTwo] = vertexTwoa.getAngle(vertexTwob);

			// Update angle at Vertex 3 that is represented by the Interger Variable "int vertexThree".
			Vector3f vertexThreea = Vector3f::normalize(value.verticies[(vertexThree + value.count - 1) % value.count] - value.verticies[vertexThree]);
			Vector3f vertexThreeb = Vector3f::normalize(value.verticies[vertexTwo] - value.verticies[vertexThree]);
			angles[vertexThree] = vertexThreea.getAngle(vertexThreeb);

			// Set the current angle to max() so that it will not be selected again.
			angles[smallest] = std::numeric_limits<float>::max();
		}
	}

	return in;
}
