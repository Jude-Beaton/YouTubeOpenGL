#include "VAO.h"

VAO::VAO()
{
	// Generate one vertex array and store name in ID
	glGenVertexArrays(1, &ID);
}

// Link a Vertex Buffer Object to the Vertex Array Object using a certain layout
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	// Set the global OpenGL buffer to VBO
	VBO.Bind();
	// Define the vertex attributes characteristics
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
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
