#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

	//Specify colour of background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	
	// Clean back buffer and assign new colour to it
	glClear(GL_COLOR_BUFFER_BIT);

	// Swap back and front buffer
	glfwSwapBuffers(window);

	// While window hasn't been closed
	while (!glfwWindowShouldClose(window))
	{
		// Take care of all glfw events
		glfwPollEvents();
	}

	// Destroy window and terminate glfw before closing
	glfwDestroyWindow(window);
	glfwTerminate();
	
	return 0;
}