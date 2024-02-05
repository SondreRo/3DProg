#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

Camera::Camera()
{
    viewMemoryLocation = NULL;
}

Camera::Camera(unsigned int inShaderProgram)
{
    viewMemoryLocation = glGetUniformLocation(inShaderProgram, "view");
}

void Camera::AddShaderProgramPath(unsigned inShaderProgram)
{
    viewMemoryLocation = glGetUniformLocation(inShaderProgram, "view");
}

void Camera::tick(float DeltaTime)
{    

    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    glUniformMatrix4fv(viewMemoryLocation, 1, GL_FALSE, glm::value_ptr(view));
}

void Camera::AddMovement(glm::vec3 Direction, float Speed, float DeltaTime)
{
    cameraPos += Speed * Direction * cameraSpeed * DeltaTime;
}

void Camera::AddRotation(float mouseX, float mouseY)
{
    if (firstMouse)
    {
        lastX = mouseX;
        lastY = mouseY;
        firstMouse = false;
    }
    float xoffset = mouseX - lastX;
    float yoffset = lastY - mouseY;
    lastX = mouseX;
    lastY = mouseY;
    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    yaw += xoffset;
    pitch += yoffset;
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
    cameraRight = glm::normalize(glm::cross(glm::vec3(0.0f,1.0f,0.0f), cameraFront));

}

glm::vec3 Camera::GetForwardVector()
{

    return cameraFront;
}

glm::vec3 Camera::GetRightVector()
{
    return cameraRight;
}

glm::vec3 Camera::GetUpVector()
{
    return cameraUp;
}

glm::vec3 Camera::GetLocation()
{
    return cameraPos;
}

void Camera::SetSpeed(float newSpeed)
{
    if (newSpeed < 0.1)
    {
        newSpeed = 0.1f;
    }
    else if (newSpeed > 100)
    {
        newSpeed = 100;
    }
    cameraSpeed = newSpeed;
}

float Camera::GetSpeed()
{
    return cameraSpeed;
}
