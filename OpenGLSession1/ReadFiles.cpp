#include "ReadFiles.h"

#include <iostream>
#include <fstream>
#include <sstream>

std::vector<Vertex> ReadFiles::ReadFileVertexData(const char* path)
{
	std::vector<Vertex> vertices;
	std::ifstream in;
	in.open(path);
	if (in.is_open())
	{
		std::string line;
		std::getline(in,line);
		std::cout << line << '\n';
		int amountOfPoints = std::stoi(line);
		while (std::getline(in,line) )
		{
			Vertex tempVertex;
			tempVertex.x = std::stof(line.substr(0, line.find(',')));
			line.erase(0, line.find(',') + 1);
			tempVertex.y = std::stof(line.substr(0, line.find(',')));
			line.erase(0, line.find(',') + 1);
			tempVertex.z = std::stof(line.substr(0, line.find(',')));
			line.erase(0, line.find(',') + 1);
			tempVertex.r = std::stof(line.substr(0, line.find(',')));
			line.erase(0, line.find(',') + 1);
			tempVertex.g = std::stof(line.substr(0, line.find(',')));
			line.erase(0, line.find(',') + 1);
			tempVertex.b = std::stof(line.substr(0, line.find(',')));	
			vertices.push_back(tempVertex);
			
		}
		in.close();
	}
	else
	{
		std::cout << "Failed to open file: " << path << std::endl;
	}

	return vertices;
}

std::string ReadFiles::ReadFileString(const char* path)
{
	std::ifstream in;
	in.open(path);
	if (in.is_open())
	{
		std::stringstream buffer;
		buffer << in.rdbuf();
		std::string fileString = buffer.str();
		in.close();
		return fileString;
	}
	else
	{
				std::cout << "Failed to open file: " << path << std::endl;
		return "";
	}
}

void ReadFiles::ReadOBJ(const char* path, std::vector<Vertex>& Vertices, std::vector<Triangle>& Triangles)
{
	std::ifstream in;
	in.open(path);
	std::string line;
	if (in.is_open())
	{
		while (!in.eof())
		{
			char firstChar;
			in >> firstChar;

			switch (firstChar)
			{
			case '#':
				std::getline(in, line);
				std::cout << line << std::endl;
				break;

			case 'v':
				float x, y, z, r, g, b;
				in >> x
				>> y
				>> z
				>> r
				>> g
				>> b;

				Vertices.emplace_back(x,y,z,r,g,b);
				break;

			case 'f':
				unsigned int my0, my1, my2;
				in >> my0 >> my1 >> my2;
				Triangles.emplace_back(my0-1,my1-1,my2-1);
				break;
			default:
				std::getline(in, line);
				break;
			}
		}
		std::cout << "ModelLoaded";
		in.close();
	}
}
