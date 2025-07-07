#version 330 core
// Positions
layout (location = 0) in vec3 aPos;
// Normals
layout (location = 1) in vec3 aNormal;
// Colours
layout (location = 2) in vec3 aColor;
// Textures
layout (location = 3) in vec2 aTex;


out vec3 crntPos;
out vec3 Normal;
// Outputs colour for the fragment shader
out vec3 color;
// Outputs texture coordinates to the fragment shader
out vec2 texCoord;




uniform mat4 camMatrix;
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;


void main()
{
   crntPos = vec3(model * translation * -rotation * scale * vec4(aPos, 1.0f));

   Normal = vec3(model * vec4(aNormal, 1.0f));
   // Assigns the colours from the Vertex Data to "color"
   color = aColor;
   // Assigns the texture coordinates from the Vertex Data to "texCoord"
   texCoord = mat2(0.0f, -1.0f, 1.0f, 0.0f) * aTex;
   
   // Outputs the positions/coordinates of vertices
   gl_Position = camMatrix * vec4(crntPos, 1.0);
}