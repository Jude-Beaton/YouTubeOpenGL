#version 330 core

// Outputs colours in RGBA
out vec4 FragColor;

// Inputs coulour from Vertex Shader
in vec3 color;
// Inputs texture coords from Vertex Shader
in vec2 texCoord;

in vec3 Normal;
in vec3 crntPos;

// Gets Texture unit from main function
uniform sampler2D diffuse0;

uniform sampler2D specular0;

uniform vec4 lightColor;

uniform vec3 lightPos;
uniform vec3 camPos;

vec4 pointLight()
{
   vec3 lightVec = lightPos - crntPos;
   float dist = length(lightVec);
   float a = 0.05f;
   float b = 0.05f;
   float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);


   float ambient = 1.50f;

   vec3 normal = normalize(Normal);
   vec3 lightDirection = normalize(lightVec);

   float diffuse = max(dot(normal, lightDirection), 0.0f);

   float specularLight = 0.50f;
   vec3 viewDirection = normalize(camPos - crntPos);
   vec3 reflectionDirection = reflect(-lightDirection, normal);
   float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 32);
   float specular = specAmount * specularLight;

   return vec4(texture(diffuse0, texCoord).rgb * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten, 1.0f) * lightColor;

}

vec4 directLight()
{
   float ambient = 0.20f;

   vec3 normal = normalize(Normal);
   vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));

   float diffuse = max(dot(normal, lightDirection), 0.0f);

   float specularLight = 0.50f;
   vec3 viewDirection = normalize(camPos - crntPos);
   vec3 reflectionDirection = reflect(-lightDirection, normal);
   float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 32);
   float specular = specAmount * specularLight;

   return vec4(texture(diffuse0, texCoord).rgb * (diffuse + ambient) + texture(specular0, texCoord).r * specular, 1.0f) * lightColor;

}

vec4 spotLight()
{
   float outerCone = 0.90f;
   float innerCone = 0.95f;

   float ambient = 0.20f;

   vec3 normal = normalize(Normal);
   vec3 lightDirection = normalize(lightPos - crntPos);

   float diffuse = max(dot(normal, lightDirection), 0.0f);

   float specularLight = 0.50f;
   vec3 viewDirection = normalize(camPos - crntPos);
   vec3 reflectionDirection = reflect(-lightDirection, normal);
   float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 32);
   float specular = specAmount * specularLight;

   float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
   float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

   return vec4(texture(diffuse0, texCoord).rgb * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten, 1.0f) * lightColor;
}

void main()
{
   

   FragColor = spotLight();

}