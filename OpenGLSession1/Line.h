#pragma once
#include <vector>

#include "Vertex.h"
#include "glm/glm.hpp"

class Line
{
public:
	Line();
	std::vector<Vertex> mVertices;
	glm::mat4 matrix;
	
};

