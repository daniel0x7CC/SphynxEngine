#pragma once

#include <GL\glew.h>
#include "SOIL2\SOIL2.h"
#include <iostream>s

class TerrainTexture
{
public:
	TerrainTexture();
	TerrainTexture(const char* fileLoc, const char* fileLoc1, const char* fileLoc2, const char* fileLoc3, const char* fileLoc4);
	void loadTextures();
	void bindTextures();
	void clearTexture();
	~TerrainTexture();

private:
	GLuint textureID, rTextureID, gTextureID, bTextureID, blendMapID;
	int width, height, bitDepth;
	const char* fileLocation;
	const char* fileLocation1;
	const char* fileLocation2;
	const char* fileLocation3;
	const char* fileLocation4;
};

