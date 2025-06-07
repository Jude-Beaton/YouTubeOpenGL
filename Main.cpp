#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

// Array of vertices for the equilateral triangles
GLfloat vertices[] =
{
	//   COORDINATES	   /		COLOURS			/	TEXTURE COORDS
	-0.5f, -0.5f,  0.0f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		// Bottom Left
	-0.5f,  0.5f,  0.0f,		0.0f, 1.0f, 0.0f,		0.0f, 1.0f,		// Bottom Right
	 0.5f,  0.5f,  0.0f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		// Top Right
	 0.5f, -0.5f,  0.0f,		1.0f, 1.0f, 1.0f,		1.0f, 0.0f,		// Top Left
};

// Indices representing each triangle
GLuint indices[] =
{
	0, 2, 1,	// Upper triangle
	0, 3, 2,	// Lower triangle
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

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));


	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Texture

	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load("pop_cat.png", &widthImg, &heightImg, &numColCh, 0);

	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	// GL_NEAREST - Pixelates
	// GL_LINEAR  - Interpolates
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// float flatColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "tex0");
	shaderProgram.Activate();
	glUniform1i(tex0Uni, 0);

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
		glBindTexture(GL_TEXTURE_2D, texture);
		// Bind VAO so OpenGL uses it
		VAO1.Bind();
		// Draw triangles using 9 vertices according to element array buffer
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// Swap back and front buffer
		glfwSwapBuffers(window);
		// Take care of all glfw events
		glfwPollEvents();
	}
	
	// Delete vartex arrays, buffer arrays and shader program
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	glDeleteTextures(1, &texture);
	shaderProgram.Delete();

	// Destroy window and terminate glfw before closing
	glfwDestroyWindow(window);
	glfwTerminate();
	
	return 0;
}