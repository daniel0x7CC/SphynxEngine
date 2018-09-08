#pragma once

#include <vector>
#include <string>
#include <GL\glew.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include "CommonValues.h"

#include "Mesh.h"
#include "Shader.h"

class Skybox
{
public:
	Skybox();
	Skybox(std::vector<std::string> faceLocations);
	void renderSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
	~Skybox();
private:
	Mesh* skyBoxMesh;
	Shader* skyBoxShader;
	GLuint textureID;
	GLuint uniformProjection, uniformView;
};

