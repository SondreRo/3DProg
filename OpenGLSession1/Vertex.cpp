#include "Vertex.h"

Vertex::Vertex(float inX, float inY, float inZ, float inR, float inG, float inB)
{
	x = inX;
	y = inY;
	z = inZ;

	r = inR;
	g = inG;
	b = inB;
}

Vertex::Vertex(float inX, float inY, float inZ)
{
	x = inX;
	y = inY;
	z = inZ;

	r = 0;
	g = 0;
	b = 0;
}

Vertex::Vertex()
{
	x = 0;
	y = 0;
	z = 0;

	r = 0;
	g = 0;
	b = 0;
}

void Vertex::MultiplyPos(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
}

void Vertex::MultiplyPos(float inX, float inY, float inZ)
{
	x *= inX;
	y *= inY;
	z *= inZ;
}

void Vertex::ConvertVectorToFloatVector(std::vector<Vertex>& inVector, std::vector<float>& outVector, float scale)
{
	outVector.clear();
	for (int i{}; i < inVector.size(); i++)
	{
		inVector[i].MultiplyPos(scale);
		outVector.push_back(inVector[i].x);
		outVector.push_back(inVector[i].y);
		outVector.push_back(inVector[i].z);
		outVector.push_back(inVector[i].r);
		outVector.push_back(inVector[i].g);
		outVector.push_back(inVector[i].b);

	}
}

void Vertex::ConvertVectorToFloatVector(std::vector<Vertex>& inVector, std::vector<float>& outVector, float xScale,
	float yScale, float zScale)
{
	outVector.clear();
	for (int i{}; i < inVector.size(); i++)
	{
		inVector[i].MultiplyPos(xScale, yScale, zScale);
		outVector.push_back(inVector[i].x);
		outVector.push_back(inVector[i].y);
		outVector.push_back(inVector[i].z);
		outVector.push_back(inVector[i].r);
		outVector.push_back(inVector[i].g);
		outVector.push_back(inVector[i].b);

	}
}

void Vertex::AddOffsetToVector(std::vector<Vertex>& inVector, float xOffset, float yOffset, float zOffset)
{
	for (int i{}; i < inVector.size(); i++)
	{
		inVector[i].x += xOffset;
		inVector[i].y += yOffset;
		inVector[i].z += zOffset;
	}
}
