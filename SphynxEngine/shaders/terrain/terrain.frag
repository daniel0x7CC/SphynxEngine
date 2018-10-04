#version 330 core
 
in vec2 texCoord;
in float yPos;
out vec4 outColor;

uniform sampler2D mTexture;
uniform sampler2D rTexture;
uniform sampler2D gTexture;
uniform sampler2D bTexture;
uniform sampler2D blendMap;

void main()
{
	vec4 blendMapColour = texture(blendMap, texCoord);
	float mTexAmount = 1.0f - (blendMapColour.r + blendMapColour.g + blendMapColour.b);
 
	vec4 detail0 = texture2D(mTexture, texCoord * 10.0) * mTexAmount;
	vec4 detail1 = texture2D(rTexture, texCoord * 10.0) * blendMapColour.r;
	vec4 detail2 = texture2D(gTexture, texCoord * 10.0) * blendMapColour.g;
	vec4 detail3 = texture2D(bTexture, texCoord * 10.0) * blendMapColour.b;
 
	outColor = detail0 + detail1 + detail2 + detail3;
}