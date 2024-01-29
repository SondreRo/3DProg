#pragma once
#include <vector>

class Vertex
{
public:
	Vertex(float inX, float inY, float inZ, float inR, float inG, float inB);
	Vertex(float inX, float inY, float inZ);
	Vertex();

	float x;
	float y;
	float z;

	float r;
	float g;
	float b;

	void MultiplyPos(float scalar);
	void MultiplyPos(float inX, float inY, float inZ);

	static void ConvertVectorToFloatVector(std::vector<Vertex>& inVector, std::vector<float>& outVector, float scale);
	static void ConvertVectorToFloatVector(std::vector<Vertex>& inVector, std::vector<float>& outVector, float xScale, float yScale, float zScale);
	static void AddOffsetToVector(std::vector<Vertex>& inVector, float xOffset, float yOffset, float zOffset);
};
