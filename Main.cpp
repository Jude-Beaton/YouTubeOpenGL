#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"

const unsigned int width = 1080;
const unsigned int height = 720;

// Array of vertices for the equilateral triangles
GLfloat vertices[] =
{
//		COORDINATES			/		COLOURS				/	TEXCOORD		/			NORMALS
	-0.5f,  0.0f,  0.5f,		0.83f, 0.70f, 0.44f,		0.0f, 0.0f,			 0.0f, -1.0f,  0.0f,	// Bottom
	-0.5f,  0.0f, -0.5f,		0.83f, 0.70f, 0.44f,		0.0f, 5.0f,			 0.0f, -1.0f,  0.0f,	// Bottom
	 0.5f,  0.0f, -0.5f,		0.83f, 0.70f, 0.44f,		5.0f, 5.0f,			 0.0f, -1.0f,  0.0f,	// Bottom
	 0.5f,  0.0f,  0.5f,		0.83f, 0.70f, 0.44f,		5.0f, 0.0f,			 0.0f, -1.0f,  0.0f,	// Bottom
	
	-0.5f,  0.0f,  0.5f,		0.83f, 0.70f, 0.44f,		0.0f, 0.0f,			-0.8f,  0.5f,  0.0f,	// Left
	-0.5f,  0.0f, -0.5f,		0.83f, 0.70f, 0.44f,		5.0f, 0.0f,			-0.8f,  0.5f,  0.0f,	// Left
	 0.0f,  0.8f,  0.0f,		0.92f, 0.86f, 0.76f,		2.5f, 5.0f,			-0.8f,  0.5f,  0.0f,	// Left
	
	-0.5f,  0.0f, -0.5f,		0.83f, 0.70f, 0.44f,		5.0f, 0.0f,			 0.0f,  0.5f, -0.8f,	// Back
	 0.5f,  0.0f, -0.5f,		0.83f, 0.70f, 0.44f,		0.0f, 0.0f,			 0.0f,  0.5f, -0.8f,	// Back
	 0.0f,  0.8f,  0.0f,		0.92f, 0.86f, 0.76f,		2.5f, 5.0f,			 0.0f,  0.5f, -0.8f,	// Back
	
	 0.5f,  0.0f, -0.5f,		0.83f, 0.70f, 0.44f,		0.0f, 0.0f,			 0.8f,  0.5f,  0.0f,	// Right
	 0.5f,  0.0f,  0.5f,		0.83f, 0.70f, 0.44f,		5.0f, 0.0f,			 0.8f,  0.5f,  0.0f,	// Right
	 0.0f,  0.8f,  0.0f,		0.92f, 0.86f, 0.76f,		2.5f, 5.0f,			 0.8f,  0.5f,  0.0f,	// Right
	
	 0.5f,  0.0f,  0.5f,		0.83f, 0.70f, 0.44f,		5.0f, 0.0f,			 0.0f,  0.5f,  0.8f,	// Front
	-0.5f,  0.0f,  0.5f,		0.83f, 0.70f, 0.44f,		0.0f, 0.0f,			 0.0f,  0.5f,  0.8f,	// Front
	 0.0f,  0.8f,  0.0f,		0.92f, 0.86f, 0.76f,		2.5f, 5.0f,			 0.0f,  0.5f,  0.8f,	// Front
};

// Indices representing each triangle
GLuint indices[] =
{
	 0,  1,  2,
	 0,  2,  3,
	 4,  6,  5,
	 7,  9,  8,
	10, 12, 11,
	13, 15, 14,
};  

GLfloat lightVertices[] =
{
	-0.1f, -0.1f,   0.1f,
	-0.1f, -0.1f,  -0.1f,
	 0.1f, -0.1f,  -0.1f,
	 0.1f, -0.1f,   0.1f,
	-0.1f,  0.1f,   0.1f,
	-0.1f,  0.1f,  -0.1f,
	 0.1f,  0.1f,  -0.1f,
	 0.1f,  0.1f,   0.1f,
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7,
};


int main() 
{
	// Initialise glfw
	glfwInit();
	
	// Set glfw versions
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a window
	GLFWwindow* window = glfwCreateWindow(width, height, "YoutubeOpenGL", NULL, NULL);

	// If window has not been created close the program
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}


	// Assign the window to the OpenGL context
	glfwMakeContextCurrent(window);

	// Load GLAD to configure OpenGL
	gladLoadGL();

	// Specify viewport of OpenGL in the window
	// (from top left to bottom right)
	glViewport(0, 0, width, height);


	// Initialise the shaders
	Shader shaderProgram("default.vert", "default.frag");
	
	// Bind the Vertex Array Object to OpenGL
	VAO VAO1;
	VAO1.Bind();

	// Initialise a vertex buffer object and an element index buffer
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	// Link the different attributes, coords, colour, texture coords
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

	// Unbind so they cannot be edited
	// ORDER IMPORTANT
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	Shader lightShader("light.vert", "light.frag");

	VAO lightVAO;
	lightVAO.Bind();

	VBO lightVBO(lightVertices, sizeof(lightVertices));
	EBO lightEBO(lightIndices, sizeof(lightIndices));

	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();


	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);
	
	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	

	// Initialise texture
	Texture popCat("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(shaderProgram, "tex0", 0);

	//// Variable to store rotation of object
	//float rotation = 0.0f;

	//// Variable to store time of last roation made
	//double prevTime = glfwGetTime();

	// Turn on depth testing for the faces drawn of the object
	glEnable(GL_DEPTH_TEST);

	// Initialise camera
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));


	// While window hasn't been closed
	while (!glfwWindowShouldClose(window))
	{
		// Specify colour of background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean backbuffer and fill it with specified colour
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		


		//double crntTime = glfwGetTime();
		//if (crntTime - prevTime >= 1.0f / 60.0f)
		//{
		//	rotation += 0.5f;
		//	prevTime = crntTime;
		//}

		glm::mat4 model = glm::mat4(1.0f);

		// Rotate the model matrix
		//model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));

		// Pass the matrices into the shader using the uniforms
		//int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		// Recieve inputs
		camera.Inputs(window);
		// Convert coords to the projection
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		// Specify shader program to use
		shaderProgram.Activate();
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram, "camMatrix");


		// Binds texture to appear in rendering
		popCat.Bind();
		// Bind VAO so OpenGL uses it
		VAO1.Bind();
		// Draw triangles using 9 vertices according to element array buffer
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
		
		lightShader.Activate();
		camera.Matrix(lightShader, "camMatrix");
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);


		// Swap back and front buffer
		glfwSwapBuffers(window);
		// Take care of all glfw events
		glfwPollEvents();
	}
	
	// Delete vartex arrays, buffer arrays and shader program
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	popCat.Delete();
	shaderProgram.Delete();

	// Destroy window and terminate glfw before closing
	glfwDestroyWindow(window);
	glfwTerminate();
	
	return 0;
}