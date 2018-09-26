#include "Terrain.h"

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

	vertexCount = texture_width * texture_height * 8;

	std::vector<glm::vec3> vertx(vertexCount);

	std::uint32_t index = 0, offset = 0;
	float positionX, positionZ;
	for (int x = 0; x < (texture_width - 1); ++x)
	{
		for (int z = 0; z < (texture_height - 1); ++z)
		{
			offset = (x * texture_width) + (z + 1);
			positionX = (float)x;
			positionZ = (float)(z + 1);

			vertx[index] = glm::vec3(positionX * 16.0f, pData[offset] * 1.25f, positionZ * 16.0f);
			index++;

			offset = ((x + 1) * texture_width) + (z + 1);
			positionX = (float)(x + 1);
			positionZ = (float)(z + 1);

			vertx[index] = glm::vec3(positionX * 16.0f, pData[offset] * 1.25f, positionZ * 16.0f);
			index++;

			offset = ((x + 1) * texture_width) + (z + 1);
			positionX = (float)(x + 1);
			positionZ = (float)(z + 1);

			vertx[index] = glm::vec3(positionX * 16.0f, pData[offset] * 1.25f, positionZ * 16.0f);
			index++;

			offset = ((x + 1) * texture_width) + z;
			positionX = (float)(x + 1);
			positionZ = (float)z;

			vertx[index] = glm::vec3(positionX * 16.0f, pData[offset] * 1.25f, positionZ * 16.0f);
			index++;

			offset = ((x + 1) * texture_width) + z;
			positionX = (float)(x + 1);
			positionZ = (float)z;

			vertx[index] = glm::vec3(positionX * 16.0f, pData[offset] * 1.25f, positionZ * 16.0f);
			index++;

			offset = (x * texture_width) + z;
			positionX = (float)x;
			positionZ = (float)z;

			vertx[index] = glm::vec3(positionX * 16.0f, pData[offset] * 1.25f, positionZ * 16.0f);
			index++;

			offset = (x * texture_width) + z;
			positionX = (float)x;
			positionZ = (float)z;

			vertx[index] = glm::vec3(positionX * 16.0f, pData[offset] * 1.25f, positionZ * 16.0f);
			index++;

			offset = (x * texture_width) + (z + 1);
			positionX = (float)x;
			positionZ = (float)(z + 1);

			vertx[index] = glm::vec3(positionX * 16.0f, pData[offset] * 1.25f, positionZ * 16.0f);
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
	glDrawArrays(GL_LINES, 0, vertexCount);
	glBindVertexArray(0);

	// set polygon mode to fill again
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

Terrain::~Terrain()
{

}
