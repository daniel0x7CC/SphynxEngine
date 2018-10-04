#version 330 core
in vec3 TexCoords;

out vec4 colour;

uniform samplerCube skybox;
uniform samplerCube skyboxNight;
uniform float blendFactor;


void main()
{
	colour = texture(skybox, TexCoords);
}