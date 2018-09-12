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

	std::ifstream in(path, std::ios::in);
	if (!in) { std::cerr << "Não pode abrir o arquivo: " << path << std::endl; exit(1); }

	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;

	std::string line;
	while (getline(in, line)) {
		if (line.substr(0, 2) == "v ") {
			std::istringstream s(line.substr(2));
			glm::vec3 v;
			s >> v.x; s >> v.y; s >> v.z;
			vertices.push_back(v);
		}
		else if (line.substr(0, 2) == "f ") {
			GLushort a, b, c;

			std::string temp = line.substr(2);
			std::istringstream s(temp);
			s >> a;
			s.clear();

			temp = temp.substr(4);
			s.str(temp);
			s >> b;
			s.clear();

			temp = temp.substr(5);
			s.str(temp);
			s >> c;
			s.clear();

			indices.push_back(--a);
			indices.push_back(--b);
			indices.push_back(--c);
		}
		else if (line[0] == '#') { /* ignorando esta linha */ }
		else { /* ignoring this line */ }
	}
	printf("file loaded successfully!");

	indexCount = indices.size();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), indices.data(), GL_STATIC_DRAW);

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
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
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
