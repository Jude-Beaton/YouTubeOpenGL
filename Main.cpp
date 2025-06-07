#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

// Array of vertices for the equilateral triangles
GLfloat vertices[] =
{
	-0.5f, -0.5f * float(sqrt(3)) / 3,	   0.0f,	0.8f, 0.3f,  0.02f,	// Bottom Left 
	 0.5f, -0.5f * float(sqrt(3)) / 3,     0.0f,	0.8f, 0.3f,  0.02f,	// Bottom Right
	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,	1.0f, 0.6f,  0.32f,	// Top
	-0.25f, 0.5f * float(sqrt(3)) / 6,     0.0f,	0.9f, 0.45f, 0.17f,	// Middle Left
	 0.25f, 0.5f * float(sqrt(3)) / 6,	   0.0f,	0.9f, 0.45f, 0.17f,	// Middle Right
	 0.0f, -0.5f * float(sqrt(3)) / 3,	   0.0f,	0.8f, 0.3f,  0.02f	// Middle Bottom
};

// Indices representing each triangle
GLuint indices[] =
{
	0, 3, 5,	// Lower left triangle
	3, 2, 4,	// Lower right triangle
	5, 4, 1		// Upper triangle
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
	GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL);

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
	glViewport(0, 0, 800, 800);

	Shader shaderProgram("default.vert", "default.frag");
	
	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// While window hasn't been closed
	while (!glfwWindowShouldClose(window))
	{
		// Specify colour of background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean backbuffer and fill it with specified colour
		glClear(GL_COLOR_BUFFER_BIT);
		// Specify shader program to use
		shaderProgram.Activate();
		glUniform1f(uniID, 0.5f);
		// Bind VAO so OpenGL uses it
		VAO1.Bind();
		// Draw triangles using 9 vertices according to element array buffer
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// Swap back and front buffer
		glfwSwapBuffers(window);
		// Take care of all glfw events
		glfwPollEvents();
	}
	
	// Delete vartex arrays, buffer arrays and shader program
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	// Destroy window and terminate glfw before closing
	glfwDestroyWindow(window);
	glfwTerminate();
	
	return 0;
}