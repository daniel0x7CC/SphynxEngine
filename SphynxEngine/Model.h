#pragma once

#include <vector>
#include <glm.hpp>
#include "Mesh.h"
#include "Shader.h"
#include <gtc\type_ptr.hpp>
#include <gtc\matrix_transform.hpp>

class Model
{
public:
	Model();
	~Model();
	void render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
	bool loadObj(const char * path,
		std::vector<glm::vec4> &vertices,
		std::vector<glm::vec3> &normals, std::vector<GLushort> &elements);

private:
	Shader* modelShader;
	GLuint uniformProjection, uniformView, uniformModel;
	GLuint VAO;
	Mesh* modelMesh;
	std::vector<glm::vec4> modelVertices;
};

