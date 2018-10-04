#pragma once
#include <iostream>
#include <string.h>
#include "SOIL2\SOIL2.h"
#include "GL\glew.h"
#include "Shader.h"
#include "glm.hpp"
#include <vector>
#include <gtc\type_ptr.hpp>
#include <gtc\matrix_transform.hpp>
class Terrain
{
public:
	Terrain();
	Terrain(const char* fileName);
	~Terrain();
	void renderFromHeightmap(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
private:
	GLuint uniformProjection, uniformView, uniformModel, textureLocation;
	Shader* terrainShader;
	//heighmap texture ID
	GLuint heightMapTextureID, textureID;
	//IDs for vertex array and buffer object
	GLuint vaoID;
	GLuint vboID;
	//heightmap texture dimensions and half dimensions
	 const static int TERRAIN_WIDTH = 128;
	 const static int TERRAIN_DEPTH = 128;
	 int TERRAIN_HALF_WIDTH = TERRAIN_WIDTH >> 1;
	 int TERRAIN_HALF_DEPTH = TERRAIN_DEPTH >> 1;
	//heightmap height scale and half scale values
	float scale = 50;
	float half_scale = scale / 2.0f;

	//total vertices and indices in the terrain
	 const static int TOTAL = (TERRAIN_WIDTH*TERRAIN_DEPTH);
	 const static int TOTAL_INDICES = TOTAL * 2 * 3;

	//projection and modelview matrices
	glm::mat4  P = glm::mat4(1);
	glm::mat4 MV = glm::mat4(1);
	GLuint rTextureLocation, gTextureLocation, bTextureLocation, blendMapLocation, bgTextureLocation;
	std::uint32_t vertexCount = 0;
};

