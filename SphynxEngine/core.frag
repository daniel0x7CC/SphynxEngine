#version 330 core
in vec4 vCol;
in vec2 texCoord;

out vec4 colour;
uniform sampler2D mTexture;

void main()
{
	colour = texture(mTexture, texCoord);
}