#version 330 core
// Positions
layout (location = 0) in vec3 aPos;
// Colours
layout (location = 1) in vec3 aColor;
// Textures
layout (location = 2) in vec2 aTex;

// Outputs colour for the fragment shader
out vec3 color;
// Outputs texture coordinates to the fragment shader
out vec2 texCoord;

uniform mat4 camMatrix;


void main()
{
   // Outputs the positions/coordinates of vertices
   gl_Position = camMatrix * vec4(aPos, 1.0);
   // Assigns the colours from the Vertex Data to "color"
   color = aColor;
   // Assigns the texture coordinates from the Vertex Data to "texCoord"
   texCoord = aTex;
}