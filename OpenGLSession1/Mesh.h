#pragma once
#include <string>

#include "Vertex.h"
#include "Triangle.h"
#include <vector>
#include <glm/glm.hpp>
class Mesh
{
private:
	int modelLocation;
	std::string Name;
public:
	unsigned int VBO, VAO, EBO;
	Mesh();
	std::vector<Vertex> vertices;
	std::vector<Triangle> indices;

	void Bind(unsigned int ShaderProgram);
	void Draw();
	void CleanUp();

	glm::mat4 modelMat;

	std::string GetName();
	void SetName(std::string NewName);

	glm::vec3 GetLocation();
	glm::quat GetRotation();
};

