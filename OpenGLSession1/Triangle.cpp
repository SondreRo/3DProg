#include "Triangle.h"

Triangle::Triangle()
{
	
}

Triangle::Triangle(int Vert1, int Vert2, int Vert3)
{
	VerticesIndex.push_back(Vert1);
	VerticesIndex.push_back(Vert2);
	VerticesIndex.push_back(Vert3);
}

void Triangle::ConvertArrayToVector(std::vector<Triangle>& Triangles, std::vector<unsigned>& inVerticesIndex)
{
	for (int i = 0; i < Triangles.size(); i++)
	{
		inVerticesIndex.push_back(Triangles[i].VerticesIndex[0]);
		inVerticesIndex.push_back(Triangles[i].VerticesIndex[1]);
		inVerticesIndex.push_back(Triangles[i].VerticesIndex[2]);

	}
}
