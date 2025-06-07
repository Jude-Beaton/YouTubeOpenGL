#include "VAO.h"

VAO::VAO()
{
	// Generate one vertex array and store name in ID
	glGenVertexArrays(1, &ID);
}

// Link a Vertex Buffer Object to the Vertex Array Object using a certain layout
void VAO::LinkVBO(VBO& VBO, GLuint layout)
{
	// Set the global OpenGL buffer to VBO
	VBO.Bind();
	// Define the vertex attributes characteristics
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	// Enables the vertex attribute
	glEnableVertexAttribArray(layout);
	// Unbind the buffer to prevent unwanted editing
	VBO.Unbind();
}

void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}
