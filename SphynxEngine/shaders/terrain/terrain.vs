#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 textCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 texCoord;
out float yPos;

void main()
{
	gl_Position = projection * view * model * vec4(pos, 1.0);
	texCoord = textCoords;
	yPos = pos.y;	
}