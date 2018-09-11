#include "Model.h"

Model::Model()
{
	/*modelShader = new Shader();
	modelShader->createFromFiles("shaders/model.vs", "shaders/model.frag");

	uniformProjection = modelShader->getProjectionLocation();
	uniformView = modelShader->getViewLocation();*/
}

bool Model::loadObj(const char * path,
	std::vector<glm::vec4> &vertices,
	 std::vector<glm::vec3> &normals, std::vector<GLushort> &elements)
{

	modelShader = new Shader();
	modelShader->createFromFiles("shaders/model.vs", "shaders/model.frag");

	uniformProjection = modelShader->getProjectionLocation();
	uniformView = modelShader->getViewLocation();

	std::ifstream in(path, std::ios::in);
	if (!in) { std::cerr << "Não pode abrir o arquivo: " << path << std::endl; exit(1); }

	std::string line;
	while (getline(in, line)) {
		if (line.substr(0, 2) == "v ") {
			std::istringstream s(line.substr(2));
			glm::vec4 v; s >> v.x; s >> v.y; s >> v.z; v.w = 1.0f;
			vertices.push_back(v);
		}
		else if (line.substr(0, 2) == "f ") {
			std::istringstream s(line.substr(2));
			GLushort a, b, c;
			s >> a; s >> b; s >> c;
			a--; b--; c--;
			elements.push_back(a);
			elements.push_back(b); 
			elements.push_back(c);
		}
		else if (line[0] == '#') { /* ignorando esta linha */ }
		else { /* ignoring this line */ }
	}

	//normals.resize(mesh->vertices.size(), glm::vec3(0.0, 0.0, 0.0));
	/*for (int i = 0; i < elements.size(); i += 3) {
		GLushort ia = elements[i];
		GLushort ib = elements[i + 1];
		GLushort ic = elements[i + 2];
		glm::vec3 normal = glm::normalize(glm::cross(
			glm::vec3(vertices[ib]) - glm::vec3(vertices[ia]),
			glm::vec3(vertices[ic]) - glm::vec3(vertices[ia])));
		normals[ia] = normals[ib] = normals[ic] = normal;
	}*/
	modelVertices = vertices;
	printf("file loaded successfully!");
}

void Model::render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	viewMatrix = glm::mat4(glm::mat3(viewMatrix));

	glm::mat4 projection = glm::perspective(45.0f, (GLfloat) 800 / (GLfloat)600, 0.1f, 100.0f);

	glDepthMask(GL_FALSE);

	modelShader->useShader();
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
	model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, modelVertices.size() * 3);
	glBindVertexArray(0);

	glDepthMask(GL_TRUE);
}

Model::~Model()
{
}
