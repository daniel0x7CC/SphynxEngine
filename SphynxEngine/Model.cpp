#include "Model.h"

Model::Model()
{
	/*modelShader = new Shader();
	modelShader->createFromFiles("shaders/model.vs", "shaders/model.frag");

	uniformProjection = modelShader->getProjectionLocation();
	uniformView = modelShader->getViewLocation();*/
}

bool Model::loadObj(const char* path)
{
	modelShader = new Shader();
	modelShader->createFromFiles("shaders/model.vs", "shaders/model.frag");

	uniformProjection = modelShader->getProjectionLocation();
	uniformView = modelShader->getViewLocation();

	std::vector< unsigned int> vertexIndices, normals, uvIndices;
	std::vector< glm::vec3> temp_vertices;
	std::vector< glm::vec2> temp_uvs;

	FILE *fp = fopen(path, "r");

	if (fp == NULL) {
		perror("Failed: ");
		return false;
	}
	else {
		while (true)
		{
			char lineHeader[128];

			int res = fscanf(fp, "%s", lineHeader);
			if (res == EOF)
				break;

			if (strcmp(lineHeader, "v") == 0)
			{
				glm::vec3 vertex;
				fscanf(fp, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				temp_vertices.push_back(vertex);
			}
			else if (strcmp(lineHeader, "vt") == 0)
			{
				glm::vec2 uv;
				fscanf(fp, "%f %f\n", &uv.x, &uv.y);
				temp_uvs.push_back(uv);
			}
			else if (strcmp(lineHeader, "f") == 0)
			{
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(fp, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				if (matches != 9) {
					printf("File can't be read by our simple parser :-( Try exporting with other options\n");
					return false;
				}
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normals.push_back(normalIndex[0]);
				normals.push_back(normalIndex[1]);
				normals.push_back(normalIndex[2]);

			}
		}
	}
		
	
	printf("file loaded successfully!");

	indexCount = vertexIndices.size();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexIndices[0]) * temp_vertices.size(), temp_vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexIndices[0]) * vertexIndices.size(), vertexIndices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return true;
}

void Model::render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	modelShader->useShader();
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(1.0f, 0.0f, -2.5f));
	model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Model::~Model()
{
}
