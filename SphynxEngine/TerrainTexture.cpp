#include "TerrainTexture.h"


TerrainTexture::TerrainTexture()
{
	textureID = 0;
	rTextureID = 0;
	gTextureID = 0;
	bTextureID = 0;
	blendMapID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
}

TerrainTexture::TerrainTexture(const char* fileLoc, const char* fileLoc1, const char* fileLoc2, const char* fileLoc3, const char* fileLoc4)
{
	textureID = 0;
	rTextureID = 0;
	gTextureID = 0;
	bTextureID = 0;
	blendMapID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLocation = fileLoc;
	fileLocation1 = fileLoc1;
	fileLocation2 = fileLoc2;
	fileLocation3 = fileLoc3;
	fileLocation4 = fileLoc4;
}

void TerrainTexture::loadTextures()
{
	unsigned char *textureData = SOIL_load_image(fileLocation, &width, &height, &bitDepth, 0);
	if (!textureData)
	{
		printf("Failed to find: %s\n", fileLocation);
		return;
	}
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(textureData);

	width = 0;
	height = 0;
	bitDepth = 0;

	unsigned char *textureData1 = SOIL_load_image(fileLocation1, &width, &height, &bitDepth, 0);
	if (!textureData1)
	{
		printf("Failed to find: %s\n", fileLocation1);
		return;
	}
	glGenTextures(1, &rTextureID);
	glBindTexture(GL_TEXTURE_2D, rTextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData1);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(textureData1);

	width = 0;
	height = 0;
	bitDepth = 0;

	unsigned char *textureData2 = SOIL_load_image(fileLocation2, &width, &height, &bitDepth, 0);
	if (!textureData2)
	{
		printf("Failed to find: %s\n", fileLocation2);
		return;
	}
	glGenTextures(1, &gTextureID);
	glBindTexture(GL_TEXTURE_2D, gTextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData2);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(textureData2);

	width = 0;
	height = 0;
	bitDepth = 0;

	unsigned char *textureData3 = SOIL_load_image(fileLocation3, &width, &height, &bitDepth, 0);
	if (!textureData3)
	{
		printf("Failed to find: %s\n", fileLocation3);
		return;
	}
	glGenTextures(1, &bTextureID);
	glBindTexture(GL_TEXTURE_2D, bTextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData3);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(textureData3);

	width = 0;
	height = 0;
	bitDepth = 0;

	unsigned char *textureData4 = SOIL_load_image(fileLocation4, &width, &height, &bitDepth, 0);
	if (!textureData4)
	{
		printf("Failed to find: %s\n", fileLocation4);
		return;
	}
	glGenTextures(1, &blendMapID);
	glBindTexture(GL_TEXTURE_2D, blendMapID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData4);
	glGenerateMipmap(GL_TEXTURE_2D);


	SOIL_free_image_data(textureData4);
}

void TerrainTexture::bindTextures() 
{
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, rTextureID);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, gTextureID);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, bTextureID);
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, blendMapID);
}

TerrainTexture::~TerrainTexture()
{
}
