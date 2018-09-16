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


	std::string line;
	while (getline(in, line)) {
		if (line.substr(0, 2) == "v ") {
			std::istringstream s(line.substr(2));
			glm::vec3 v;
			s >> v.x; s >> v.y; s >> v.z;
			vertices.push_back(v);
		}
		else if (line.substr(0, 2) == "f ") {
			std::istringstream s(line.substr(2));
			GLuint a, b, c, temp_u;
			char temp_c;

			// v      /            vt           /            vn
			s >> a; s >> temp_c; s >> temp_u; s >> temp_c; s >> temp_u;

			// v      /            vt           /            vn
			s >> b; s >> temp_c; s >> temp_u; s >> temp_c; s >> temp_u;
			
			// v      /            vt           /            vn
			s >> c; s >> temp_c; s >> temp_u; s >> temp_c; s >> temp_u;

			indices.push_back(--a);
			indices.push_back(--b);
			indices.push_back(--c);
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
