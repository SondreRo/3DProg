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

void ReadFiles::ReadOBJ(const char* path, Mesh& inMesh)
{
	std::ifstream in;
	in.open(path);
	std::string line;
	std::string name;
	if (in.is_open())
	{
		std::cout << "-------------------------------" << std::endl;
		std::cout << "Starting to load model from: " << path << std::endl;
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

				inMesh.vertices.emplace_back(x,y,z,r,g,b);
				break;

			case 'f':
				unsigned int my0, my1, my2;
				in >> my0 >> my1 >> my2;
				inMesh.indices.emplace_back(my0-1,my1-1,my2-1);
				break;

			case 'o':
				std::getline(in, line);
				name = line;
				std::cout << "Name of Model: " << line << std::endl;
				inMesh.SetName(name);
				break;
			default:
				std::getline(in, line);
				break;
			}
		}
		in.close();
		std::cout << "Amount of Vertices: " << inMesh.vertices.size() << std::endl;
		std::cout << "Amount of Triangles: " << inMesh.indices.size() << std::endl;
	}
}
