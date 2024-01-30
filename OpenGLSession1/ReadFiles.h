#pragma once
#include <string>
#include "Vertex.h"
#include "triangle.h"
#include <vector>
class ReadFiles
{
public:
	static std::vector<Vertex>  ReadFileVertexData(const char* path);
	static std::string ReadFileString(const char* path);
	static void ReadOBJ(const char* path, std::vector<Vertex>& Vertices, std::vector<Triangle>& Triangles);
};
