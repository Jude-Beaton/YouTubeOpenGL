#include "Model.h"

const unsigned int width = 1080;
const unsigned int height = 720;


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


	// Generate shader object
	Shader shaderProgram("default.vert", "default.frag");

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	



	//// Variable to store rotation of object
	//float rotation = 0.5f;

	//// Variable to store time of last roation made
	//double prevTime = glfwGetTime();

	// Turn on depth testing for the faces drawn of the object
	glEnable(GL_DEPTH_TEST);

	// Initialise camera
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	Model model("models/sword/scene.gltf");

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
		//	rotation += rotationSpeed;
		//	prevTime = crntTime;
		//}

		//glm::mat4 model = glm::mat4(1.0f);
		//glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));

		
		// Recieve inputs
		camera.Inputs(window);
		// Convert coords to the projection
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		model.Draw(shaderProgram, camera);

		//floor.vertices.data()->position = model * floor.vertices.data()->position;

		//// Rotate the model matrix
		//model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));

		//// Pass the matrices into the shader using the uniforms
		//int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


		// Swap back and front buffer
		glfwSwapBuffers(window);
		// Take care of all glfw events
		glfwPollEvents();
	}
	
	// Delete vartex arrays, buffer arrays and shader program
	shaderProgram.Delete();

	// Destroy window and terminate glfw before closing
	glfwDestroyWindow(window);
	glfwTerminate();
	
	return 0;
}