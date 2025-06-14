#include "Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {
	
	// Assigns the type of texture object
	type = texType;

	// Stores width height and num of colour channels
	int widthImg, heightImg, numColCh;
	// Flips the image to appear the right way up
	stbi_set_flip_vertically_on_load(true);
	// Reads image from file and stores in 'bytes'
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	// Create an OpenGL texture object
	glGenTextures(1, &ID);
	// Assign tecture to a texture unit
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	// Configures the algorithm used to scale the texture
	// GL_NEAREST - Pixelates
	// GL_LINEAR  - Interpolates
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	// Configures how the texture repeats
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Lines necessary for using GL_CLAMP_TO_BORDER above
	// float flatColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	// Assigns the image to the OpenGL Texture object
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	// Generates texture mipmaps
	glGenerateMipmap(texType);

	// Deletes image data as it is now in the OpenGL Texture object
	stbi_image_free(bytes);

	// Unbind OpenGL texture object so that it can't be modified
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// Gets location of the uniform
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	// Shader needs to be activated before changing the uniform
	shader.Activate();
	// Sets value of the uniform
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}
void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}
