#version 330 core
in vec3 TexCoords;

out vec4 colour;

uniform samplerCube skybox;
uniform samplerCube skyboxNight;
uniform float blendFactor;

void main()
{
	vec4 texture1 = texture(skybox, TexCoords);
	vec4 texture2 = texture(skyboxNight, TexCoords);

	if (blendFactor == 0.5f) {
		colour = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	} else {
		colour = mix(texture1, texture2, blendFactor);
	}
	
}