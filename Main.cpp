#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Vertex shader sourcer code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// Fragement shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";



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

	// Create a vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Assigns the shader source code
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compiles the shader
	glCompileShader(vertexShader);

	// Create a fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Assigns the shader source code
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// Compiles the shader
	glCompileShader(fragmentShader);

	// Create empty program
	GLuint shaderProgram = glCreateProgram();

	// Attach the shaders to the program so they can be linked
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// Creates executeables for the vertex and fragment processors
	glLinkProgram(shaderProgram);

	// Shaders will not be deleted until they are no longer attached to the program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// Array of vertices for the equilateral triangles
	GLfloat vertices[] =
	{
		-0.5f, -0.5f, 0.0f,	// Bottom Left 
		0.5f, -0.5f, 0.0f,	// Bottom Right
		-0.5f, 0.5f, 0.0f,	// Top Left 
		0.5f, 0.5f, 0.0f,	// Top Right
	};

	// Indices representing each triangle
	GLuint indices[] =
	{
		2, 0, 1,	// Lower left triangle
		2, 1, 3	// Upper right triangle
	};

	GLuint VAO, VBO, EBO;

	// VAO must be before VBO

	// In OpenGL there is a global buffer that you assign the vertex array to,
	// this is why you create the array's, and then 'bind' them, essentially setting,
	// the global state.

	// Creates 1 vertex array object, and stores the name in VAO
	glGenVertexArrays(1, &VAO);
	
	// Creates 1 vertex buffer object, and stores the name in VBO
	glGenBuffers(1, &VBO);

	// Creates 1 element-array buffer object
	glGenBuffers(1, &EBO);

	// Assign VAO to the GL global vertex array object
	glBindVertexArray(VAO);
	// Assign VBO as the vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Static - Modified once, used many times
	// Stream - Modified once, used a few times
	// Dynamic - Modified multiple times, modified many times
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Bind EBO and define characteristics
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Defines the vertex attribute at index 0 as 
	// 3 points, of type float, to not be normalised when accessed,
	// with a offset of 3 floats between the start of each vertex,
	// with no offset at the beginning of the data block
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Enable the vertex attribute at index 0
	glEnableVertexAttribArray(0);

	// Binds OpenGL's VBO and VAO to 0 so they cant be accidentally modified
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	// Must be after VAO as the EBO is stored in the VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// While window hasn't been closed
	while (!glfwWindowShouldClose(window))
	{
		// Specify colour of background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean backbuffer and fill it with specified colour
		glClear(GL_COLOR_BUFFER_BIT);
		// Specify shader program to use
		glUseProgram(shaderProgram);
		// Bind VAO so OpenGL uses it
		glBindVertexArray(VAO);
		// Draw triangles using 9 vertices according to element array buffer
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// Swap back and front buffer
		glfwSwapBuffers(window);
		// Take care of all glfw events
		glfwPollEvents();
	}
	
	// Delete vartex arrays, buffer arrays and shader program
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	// Destroy window and terminate glfw before closing
	glfwDestroyWindow(window);
	glfwTerminate();
	
	return 0;
}