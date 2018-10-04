#include "Terrain.h"

// Structure that holds the heightmap data.
struct HeightmapData { 
	float x, y, z;
} *g_Heightmap;

struct Vertex {
	glm::vec3 pos;
	glm::vec2 uv;
} vertices;

Terrain::Terrain() {

}

Terrain::Terrain(const char* fileName)
{
	// Shader setup
	terrainShader = new Shader();
	terrainShader->createFromFiles("shaders/terrain/terrain.vs", "shaders/terrain/terrain.frag");

	uniformProjection = terrainShader->getProjectionLocation();
	uniformView = terrainShader->getViewLocation();
	uniformModel = terrainShader->getModelLocation();
	//textureLocation = terrainShader->getTexturesLocation();
	bgTextureLocation = terrainShader->getBackgroundTextureLocation();
	rTextureLocation = terrainShader->getRTextureLocation();
	gTextureLocation = terrainShader->getGTextureLocation();
	bTextureLocation = terrainShader->getBTextureLocation();
	blendMapLocation = terrainShader->getBlendMapLocation();

	// end of loading texture

	int map_width = 0, map_height = 0, channels = 0;
	GLubyte* pData = SOIL_load_image(fileName, &map_width, &map_height, &channels, SOIL_LOAD_L);

	printf("width: %d", map_width);
	printf("height: %d", map_height);

	// Create the array to hold the heightmap data.
	g_Heightmap = new HeightmapData[map_width * map_height];

	// Read the image data.
	std::uint32_t index = 0;
	for (int i = 0; i < map_width; ++i)
	{
		for (int j = 0; j < map_height; ++j)
		{
			index = (map_width * i) + j;
			g_Heightmap[index].x = (float)i * 16.0f;
			g_Heightmap[index].y = pData[index] * 1.25f;
			g_Heightmap[index].z = (float)j * 16.0f;
		}
	}

	vertexCount = map_width * map_height * 6;

	std::vector<Vertex> vertices(vertexCount);

	// Reset the index.
	index = 0;

	// Build terrain model.
	int index1, index2, index3, index4;
	for (int i = 0; i < (map_width - 1); ++i)
	{
		for (int j = 0; j < (map_height - 1); ++j)
		{
			// Get the indexes to the four points of the quad.
			index1 = (map_width * j) + i;				// Upper left.
			index2 = (map_width * j) + (i + 1);			// Upper right.
			index3 = (map_width * (j + 1)) + i;			// Bottom left.
			index4 = (map_width * (j + 1)) + (i + 1);	// Bottom right.

			// Create two triangles for the quad.
			// Triangle 1 - Upper left.
			vertices[index].pos.x = g_Heightmap[index1].x;
			vertices[index].pos.y = g_Heightmap[index1].y;
			vertices[index].pos.z = g_Heightmap[index1].z;

			vertices[index].uv.x = (float)i / (float)(map_width - 1);
			vertices[index].uv.y = (float)j / (float)(map_height - 1);
			index++;

			// Triangle 1 - Upper right.
			vertices[index].pos.x = g_Heightmap[index2].x;
			vertices[index].pos.y = g_Heightmap[index2].y;
			vertices[index].pos.z = g_Heightmap[index2].z;
		
			vertices[index].uv.x = (float)(i + 1) / (float)(map_width - 1);
			vertices[index].uv.y = (float)j / (float)(map_height - 1);

			index++;

			// Triangle 1 - Bottom left.
			vertices[index].pos.x = g_Heightmap[index3].x;
			vertices[index].pos.y = g_Heightmap[index3].y;
			vertices[index].pos.z = g_Heightmap[index3].z;
			vertices[index].uv.x = (float)i / (float)(map_width - 1);
			vertices[index].uv.y = (float)(j + 1) / (float)(map_height - 1);

			index++;

			// Triangle 2 - Bottom left.
			vertices[index].pos.x = g_Heightmap[index3].x;
			vertices[index].pos.y = g_Heightmap[index3].y;
			vertices[index].pos.z = g_Heightmap[index3].z;
			vertices[index].uv.x = (float)i / (float)(map_width - 1);
			vertices[index].uv.y = (float)(j + 1) / (float)(map_height - 1);
			index++;

			// Triangle 2 - Upper right.
			vertices[index].pos.x = g_Heightmap[index2].x;
			vertices[index].pos.y = g_Heightmap[index2].y;
			vertices[index].pos.z = g_Heightmap[index2].z;
			vertices[index].uv.x = (float)(i + 1) / (float)(map_width - 1);
			vertices[index].uv.y = (float)j / (float)(map_height - 1);
			index++;

			// Triangle 2 - Bottom right.
			vertices[index].pos.x = g_Heightmap[index4].x;
			vertices[index].pos.y = g_Heightmap[index4].y;
			vertices[index].pos.z = g_Heightmap[index4].z;
			vertices[index].uv.x = (float)(i + 1) / (float)(map_width - 1);
			vertices[index].uv.y = (float)(j + 1) / (float)(map_height - 1);
			index++;
		}
	}

	//free SOIL image data
	SOIL_free_image_data(pData);

	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) sizeof(glm::vec3));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Terrain::renderFromHeightmap(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
	terrainShader->useShader();

	glUniform1i(bgTextureLocation, 1);
	glUniform1i(rTextureLocation, 2);
	glUniform1i(gTextureLocation, 3);
	glUniform1i(bTextureLocation, 4);
	glUniform1i(blendMapLocation, 5);

	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0.0f, -5.0f, -4.0f));
	model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

	// set polygon mode to draw lines
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBindVertexArray(vaoID);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	glBindVertexArray(0);

	// set polygon mode to fill again
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

Terrain::~Terrain()
{
	if (g_Heightmap)
	{
		delete[] g_Heightmap;
		g_Heightmap = 0;
	}
}
