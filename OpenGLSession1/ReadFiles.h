#pragma once
#include <string>
#include "Vertex.h"
#include <vector>
class ReadFiles
{
public:
	static std::vector<Vertex>  ReadFileVertexData(const char* path);
	static std::string ReadFileString(const char* path);
};
