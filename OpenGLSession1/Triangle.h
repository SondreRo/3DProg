#pragma once
#include <array>
#include <vector>
#include "Vertex.h"
class Triangle
{
public:
	Triangle();
	Triangle(int Vert1, int Vert2, int Vert3);
	std::vector<unsigned int> VerticesIndex;

	static void ConvertArrayToVector(std::vector<Triangle>& Triangles, std::vector<unsigned int>& VerticesIndex);
};

