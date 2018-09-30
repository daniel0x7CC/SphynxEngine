#include "Terrain.h"

// Structure that holds the heightmap data.
struct HeightmapData { float x, y, z; } *g_Heightmap;

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

	int texture_width = 0, texture_height = 0, channels = 0;
	GLubyte* pData = SOIL_load_image(fileName, &texture_width, &texture_height, &channels, SOIL_LOAD_L);

	printf("width: %d", texture_width);
	printf("height: %d", texture_height);

	// Create the array to hold the heightmap data.
	g_Heightmap = new HeightmapData[texture_width * texture_height];

	// Read the image data.
	std::uint32_t index = 0;
	for (int i = 0; i < texture_width; ++i)
	{
		for (int j = 0; j < texture_height; ++j)
		{
			index = (texture_width * i) + j;
			g_Heightmap[index].x = (float)i * 16.0f;
			g_Heightmap[index].y = pData[index] * 1.25f;
			g_Heightmap[index].z = (float)j * 16.0f;
		}
	}

	vertexCount = texture_width * texture_height * 6;
	std::vector<glm::vec3> vertx(vertexCount);

	// Reset the index.
	index = 0;

	// Build terrain model.
	int index1, index2, index3, index4;
	for (int i = 0; i < (texture_width - 1); ++i)
	{
		for (int j = 0; j < (texture_height - 1); ++j)
		{
			// Get the indexes to the four points of the quad.
			index1 = (texture_width * j) + i;				// Upper left.
			index2 = (texture_width * j) + (i + 1);			// Upper right.
			index3 = (texture_width * (j + 1)) + i;			// Bottom left.
			index4 = (texture_width * (j + 1)) + (i + 1);	// Bottom right.

			// Create two triangles for the quad.
			// Triangle 1 - Upper left.
			vertx[index].x = g_Heightmap[index1].x;
			vertx[index].y = g_Heightmap[index1].y;
			vertx[index].z = g_Heightmap[index1].z;
			index++;

			// Triangle 1 - Upper right.
			vertx[index].x = g_Heightmap[index2].x;
			vertx[index].y = g_Heightmap[index2].y;
			vertx[index].z = g_Heightmap[index2].z;
			index++;

			// Triangle 1 - Bottom left.
			vertx[index].x = g_Heightmap[index3].x;
			vertx[index].y = g_Heightmap[index3].y;
			vertx[index].z = g_Heightmap[index3].z;
			index++;

			// Triangle 2 - Bottom left.
			vertx[index].x = g_Heightmap[index3].x;
			vertx[index].y = g_Heightmap[index3].y;
			vertx[index].z = g_Heightmap[index3].z;
			index++;

			// Triangle 2 - Upper right.
			vertx[index].x = g_Heightmap[index2].x;
			vertx[index].y = g_Heightmap[index2].y;
			vertx[index].z = g_Heightmap[index2].z;
			index++;

			// Triangle 2 - Bottom right.
			vertx[index].x = g_Heightmap[index4].x;
			vertx[index].y = g_Heightmap[index4].y;
			vertx[index].z = g_Heightmap[index4].z;
			index++;
		}
	}

	//free SOIL image data
	SOIL_free_image_data(pData);

	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertx[0]) * vertx.size(), vertx.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	std::cout << "Initialization successful" << std::endl;
}

void Terrain::renderFromHeightmap(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {

	terrainShader->useShader();
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

	// set polygon mode to draw lines
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBindVertexArray(vaoID);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	glBindVertexArray(0);

	// set polygon mode to fill again
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

Terrain::~Terrain()
{
	if (g_Heightmap)
	{
		delete[] g_Heightmap;
		g_Heightmap = 0;
	}
}
