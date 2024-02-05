#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>
#include "Vertex.h"
#include "ReadFiles.h"
#include <vector>
#include "MyObject.h"
#include "glad/glad.h"
#include "Triangle.h"
#include "stb_image.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Line.h"
#include "Camera.h"
#include "Mesh.h"
#include "glm/gtx/rotate_vector.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

// Vertex Shader
std::string vertexShaderString = ReadFiles::ReadFileString("vertexShader.glsl");
const char* vertexShaderSource = vertexShaderString.c_str();

// Fragment Shader
std::string fragmentShaderString = ReadFiles::ReadFileString("fragmentShader.glsl");
const char* fragmentShaderSource = fragmentShaderString.c_str();

float Rotation = 0;
float OtherRotation = 0;

float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

float Zoom = 45;


Camera myCamera;
std::vector<Mesh*> Meshes;
Mesh* SelectedMesh;
int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(0);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);


    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    //// LOADING SHADERS.
    //int width, height, nrChannels;
    //unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
    //

    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check forvertexShader shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    myCamera.AddShaderProgramPath(shaderProgram);


    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_DEPTH_TEST);

    
    Mesh MyTestMesh;
    Mesh MyTestMeshMonke;
    Mesh Mountain;
    Meshes.push_back(&MyTestMesh);
    Meshes.push_back(&MyTestMeshMonke);
    Meshes.push_back(&Mountain);



    ReadFiles::ReadOBJ("C:/Users/soroe/Documents/CubeToTestWith.obj", MyTestMesh);
    ReadFiles::ReadOBJ("C:/Users/soroe/Documents/monke.obj", MyTestMeshMonke);
    ReadFiles::ReadOBJ("C:/Users/soroe/Documents/mountain1.obj", Mountain);


	for (auto Mesh : Meshes)
    {
        Mesh->Bind(shaderProgram);
    }

 
   
    MyTestMeshMonke.modelMat = glm::translate(glm::mat4(1), glm::vec3(3, 0, 0));
	Mountain.modelMat = glm::translate(glm::mat4(1), glm::vec3(-3, 0, 0));

    // render loop
    // -----------
    int projectionlLocation = glGetUniformLocation(shaderProgram, "projection");
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        //float timeValue = glfwGetTime();
        //float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        //int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        //std::cout << 1 / deltaTime << std::endl;

        // Matrix
        // CAMERA
        myCamera.tick(deltaTime);


        // Model 
    
        // VIEW
        //glm::mat4 view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    	// Projection

        glm::mat4 projection = glm::perspective(glm::radians(Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.01f, 1000.0f);

 

         /// SEND TO CAMERA
        

       
        glUniformMatrix4fv(projectionlLocation, 1, GL_FALSE, glm::value_ptr(projection));


    	glUseProgram(shaderProgram);
      

         // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glLineWidth(4);
        glPointSize(5);
        //glDrawArrays(GL_LINES, 0, VectorToDraw.size()/6);

        /////////////////////// THIS WORKS:
    	//glDrawArrays(GL_LINE_STRIP, 0, MyVectorOfPoints.size()); // use GL_LINE_STRIP
        //glDrawArrays(GL_LINES, MyVectorOfPoints.size(), myobject.vertices.size()-1);
        //////////////////////

        //MyTestMeshMonke.modelMat = glm::translate(MyTestMeshMonke.modelMat, glm::vec3(1*deltaTime, 0, 0));
        MyTestMeshMonke.modelMat = glm::rotate(MyTestMeshMonke.modelMat, 0.5f * deltaTime, glm::vec3(1.0f, 0.0f, 0.0f));
        for (auto Mesh : Meshes)
        {
            Mesh->Draw();
        }

        
        // glBindVertexArray(0); // no need to unbind it every time 

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------

    for (auto Mesh : Meshes)
    {
        Mesh->CleanUp();
    }
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

Mesh* GetClosestMesh(std::vector<Mesh*> &inMeshes, Camera inCamera)
{
    float ClosestDistance = 100000000;
    Mesh* ClosestMesh = inMeshes[0];
    for (auto mesh : inMeshes)
    {
        float currentDistance = glm::distance(inCamera.GetLocation(), mesh->GetLocation());
	    if (currentDistance < ClosestDistance)
	    {
            ClosestMesh = mesh;
            ClosestDistance = currentDistance;
	    }
    }
    SelectedMesh = ClosestMesh;
	return ClosestMesh;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);


    // // // Change Poligon mode
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
 

    // // // Camera Input
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        myCamera.AddMovement(myCamera.GetForwardVector(), 1, deltaTime);
    }
		
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        myCamera.AddMovement(-myCamera.GetForwardVector(), 1, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        myCamera.AddMovement(myCamera.GetRightVector(), 1, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        myCamera.AddMovement(-myCamera.GetRightVector(),1, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        myCamera.AddMovement(myCamera.GetUpVector(), 1, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        myCamera.AddMovement(-myCamera.GetUpVector(),1, deltaTime);
    }


    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        myCamera.SetSpeed(myCamera.GetSpeed() + 1.0f*deltaTime);
        std::cout << myCamera.GetSpeed() << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        myCamera.SetSpeed(myCamera.GetSpeed() - 1.0f * deltaTime);
        std::cout << myCamera.GetSpeed() << std::endl;
    }

    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
    {
        std::cout << GetClosestMesh(Meshes, myCamera)->GetName() << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
       if(SelectedMesh)
       {
           SelectedMesh->modelMat = glm::rotate(SelectedMesh->modelMat, 1.0f * deltaTime, glm::vec3(0, 1, 0));
       }
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        if (SelectedMesh)
        {
            SelectedMesh->modelMat = glm::rotate(SelectedMesh->modelMat, -1.0f * deltaTime, glm::vec3(0, 1, 0));
        }
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    SCR_HEIGHT = height;
    SCR_WIDTH = width;
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    myCamera.AddRotation(xpos, ypos);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}