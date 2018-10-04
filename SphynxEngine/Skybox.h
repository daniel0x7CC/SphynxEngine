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
	void renderSkybox(GLfloat deltaTime, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
	void loadNightFaces(std::vector<std::string> nightFaceLocations);
	~Skybox();
private:
	Mesh* skyBoxMesh;
	Shader* skyBoxShader;
	GLuint textureID, textureNightID;
	GLuint uniformProjection, uniformView, skyBoxDay, skyBoxNight, blendFactor;
	GLuint VAO;
	GLfloat ROTATE_SPEED = 1.0f;
	GLfloat rotation = 0.0f;
};

