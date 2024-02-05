#pragma once
#include <array>
#include <vector>
#include "Vertex.h"
class Triangle
{
public:
	Triangle();
	Triangle(int Vert1, int Vert2, int Vert3);
	unsigned int vert1;
	unsigned int vert2;
	unsigned int vert3;

};

