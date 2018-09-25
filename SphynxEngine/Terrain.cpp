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

	int texture_width = 0, texture_height = 0, channels = 0;
	GLubyte* pData = SOIL_load_image(fileName, &texture_width, &texture_height, &channels, SOIL_LOAD_L);

	printf("width: %d", texture_width);
	printf("height: %d", texture_height);

	std::vector<glm::vec3> vertx;
	int numIndices = (texture_width - 1)*(texture_height - 1) * 6;
	
	
	for (int x = 0; x < texture_width; ++x) {
		 for (int z = 0; z < texture_height; ++z) {
			 int offset = (x * texture_width) + z;
			 vertx[offset] = glm::vec3(
				 x * 16.0f , pData[offset] * 1.25f, z * 16.0f);
		}
	}

	for (int x = 0; x < texture_width - 1; ++x) {
		 for (int z = 0; z < texture_height - 1; ++z) {
			 int a = (x * (texture_width)) + z;
			 int b = ((x + 1) * (texture_width)) + z;
			 int c = ((x + 1) * (texture_width)) + (z + 1);
			 int d = (x * (texture_width)) + (z + 1);
			
			indices[numIndices++] = c;
			 indices[numIndices++] = b;
			 indices[numIndices++] = a;
			
			indices[numIndices++] = a;
			indices[numIndices++] = d;
			indices[numIndices++] = c;
		}
		
	}


	////setup OpenGL texture
	//glGenTextures(1, &heightMapTextureID);
	//glBindTexture(GL_TEXTURE_2D, heightMapTextureID);

	////fill indices array
	//GLuint* id = &indices[0];
	//int i = 0, j = 0;

	////setup vertices 
	//int count = 0;
	////fill terrain vertices
	//for (j = 0; j < TERRAIN_DEPTH; j++) {
	//	for (i = 0; i < TERRAIN_WIDTH; i++) {
	//		vertices[count] = glm::vec3((float(i) / (TERRAIN_WIDTH - 1)),
	//			0,
	//			(float(j) / (TERRAIN_DEPTH - 1)));
	//		count++;
	//	}
	//}

	////fill terrain indices
	//for (i = 0; i < TERRAIN_DEPTH - 1; i++) {
	//	for (j = 0; j < TERRAIN_WIDTH - 1; j++) {
	//		int i0 = j + i * TERRAIN_WIDTH;
	//		int i1 = i0 + 1;
	//		int i2 = i0 + TERRAIN_WIDTH;
	//		int i3 = i2 + 1;
	//		*id++ = i0;
	//		*id++ = i2;
	//		*id++ = i1;
	//		*id++ = i1;
	//		*id++ = i2;
	//		*id++ = i3;
	//	}
	//}

	//glBindBuffer(GL_ARRAY_BUFFER, vboVerticesID);
	////pass terrain vertices to buffer object
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

	////enable vertex attribute array for position
	//glEnableVertexAttribArray(terrainShader->getVertexLocation());
	//glVertexAttribPointer(terrainShader->getVertexLocation(), 3, GL_FLOAT, GL_FALSE, 0, 0);

	////pass the terrain indices array to element array buffer
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndicesID);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);
	//
	//	//load the heightmap texture using SOIL	
	//int texture_width = 0, texture_height = 0, channels = 0;
	//GLubyte* pData = SOIL_load_image(fileName, &texture_width, &texture_height, &channels, SOIL_LOAD_L);

	////vertically flip the heightmap image on Y axis since it is inverted 
	//for (j = 0; j * 2 < texture_height; ++j)
	//{
	//	int index1 = j * texture_width;
	//	int index2 = (texture_height - 1 - j) * texture_width;
	//	for (i = texture_width; i > 0; --i)
	//	{
	//		GLubyte temp = pData[index1];
	//		pData[index1] = pData[index2];
	//		pData[index2] = temp;
	//		++index1;
	//		++index2;
	//	}
	//}

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, texture_width, texture_height, 0, GL_RED, GL_UNSIGNED_BYTE, pData);

	//free SOIL image data
	SOIL_free_image_data(pData);

	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertx[0]) * vertx.size(), vertx.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &iboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size, indices.data() , GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//set polygon mode to draw lines
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	std::cout << "Initialization successfull" << std::endl;
}

void Terrain::renderFromHeightmap(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {

	terrainShader->useShader();
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0.5f, -3.0f, -2.5f));
	model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

	glBindVertexArray(vaoID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Terrain::~Terrain()
{

}
