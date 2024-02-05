#include "Mesh.h"

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include "glm/gtx/quaternion.hpp"

Mesh::Mesh()
{
    modelMat = glm::mat4(1.0f);
    
}

void Mesh::Bind(unsigned int ShaderProgram)
{
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(Triangle), indices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    int modelLocation = glGetUniformLocation(ShaderProgram, "model");
}

void Mesh::Draw()
{

    //modelMat = glm::translate(glm::mat4(1.0f), Location);
    //modelMat += glm::rotate(glm::mat4(1.0f), 1.0f, Rotation);
    
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMat));
    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, indices.size()*3, GL_UNSIGNED_INT, 0);
}

void Mesh::CleanUp()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

std::string Mesh::GetName()
{
    return Name;
}

void Mesh::SetName(std::string NewName)
{
    Name = NewName;
}


glm::vec3 Mesh::GetLocation()
{
    glm::mat4 transformation = modelMat; // your transformation matrix.
    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 translation;
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(transformation, scale, rotation, translation, skew, perspective);
    rotation = glm::conjugate(rotation);
    return translation;
}

glm::quat Mesh::GetRotation()
{
    glm::mat4 transformation = modelMat; // your transformation matrix.
    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 translation;
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(transformation, scale, rotation, translation, skew, perspective);
    rotation = glm::conjugate(rotation);
    return rotation;
}
