#version 330 core

// Outputs colours in RGBA
out vec4 FragColor;

// Inputs coulour from Vertex Shader
in vec3 color;
// Inputs texture coords from Vertex Shader
in vec2 texCoord;

// Gets Texture unit from main function
uniform sampler2D tex0;

void main()
{
   FragColor = texture(tex0, texCoord);
}