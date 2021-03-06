#version 330 core
layout (location = 0) in vec3 pos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec4 color;

void main()
{
	gl_Position = projection * view * model * vec4(pos, 1.0);
	color = vec4(1.0f, 0.0f, 1.0f, 1.0f);
}