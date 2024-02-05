#pragma once
#include "glm/glm.hpp"
class Camera
{
private:

	unsigned int viewMemoryLocation;


	float yaw = 0;
	float pitch = 0;
	float roll = 0;

	// CameraLocation
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f); // Start Position
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	// CameraRotation
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::vec3(0.1f,0.0f,0.0f);

	float cameraSpeed = 2.5f;

	glm::vec3 cameraDirection = glm::vec3(0.0f, 1.0f, 0.0f);;


	float lastX = 400, lastY = 300;
	bool firstMouse = true;
public:
	Camera();
	Camera(unsigned int inShaderProgram);
	void AddShaderProgramPath(unsigned int inShaderProgram);
	void tick(float DeltaTime);
	void AddMovement(glm::vec3 Direction, float Speed, float DeltaTime);
	void AddRotation(float mouseX, float mouseY);

	glm::vec3 GetForwardVector();
	glm::vec3 GetRightVector();
	glm::vec3 GetUpVector();
	glm::vec3 GetLocation();
	
	void SetSpeed(float newSpeed);
	float GetSpeed();

};

