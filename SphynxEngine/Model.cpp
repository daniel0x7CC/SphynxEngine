#include "Model.h"

Model::Model()
{
}

bool Model::loadObj(const char* path)
{

	modelShader = new Shader();
	modelShader->createFromFiles("shaders/model.vs", "shaders/model.frag");

	uniformProjection = modelShader->getProjectionLocation();
	uniformView = modelShader->getViewLocation();

	std::ifstream in(path, std::ios::in);
	if (!in) { std::cerr << "Não pode abrir o arquivo: " << path << std::endl; exit(1); }

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<unsigned int> vertexBum, uvsIndices;

	std::string line;
	while (getline(in, line)) {
		if (line.substr(0, 2) == "v ") {
			std::istringstream s(line.substr(2));
			glm::vec3 v;
			s >> v.x; s >> v.y; s >> v.z;
			vertices.push_back(v);
		}
		else if (line.substr(0, 2) == "vt ") {
			std::istringstream s(line.substr(2));
			glm::vec2 temp_uv;
			s >> temp_uv.x; s >> temp_uv.y;
			uvs.push_back(temp_uv);
		}
		else if (line.substr(0, 2) == "f ") {
			std::istringstream s(line.substr(2));
			GLuint a, b, c, uvIndexA, uvIndexB, uvIndexC, temp_vn;
			char temp_c;

			// v      /            vt           /            vn
			s >> a; s >> temp_c; s >> uvIndexA; s >> temp_c; s >> temp_vn;

			// v      /            vt           /            vn
			s >> b; s >> temp_c; s >> uvIndexB; s >> temp_c; s >> temp_vn;
			
			// v      /            vt           /            vn
			s >> c; s >> temp_c; s >> uvIndexC; s >> temp_c; s >> temp_vn;
			
			vertexBum.push_back(--a);
			vertexBum.push_back(--b);
			vertexBum.push_back(--c);
			uvsIndices.push_back(uvIndexA);
			uvsIndices.push_back(uvIndexB);
			uvsIndices.push_back(uvIndexC);
		}
		else if (line[0] == '#') { /* ignorando esta linha */ }
		else { /* ignoring this line */ }
	}
	printf("file loaded successfully!");

	indexCount = vertexBum.size();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexBum[0]) * vertexBum.size(), vertexBum.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Model::render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	modelShader->useShader();
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0.5f, -3.0f, -2.5f));
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
