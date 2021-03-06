#include "Skybox.h"

Skybox::Skybox()
{
}

Skybox::Skybox(std::vector<std::string> faceLocations)
{
	// Shader setup
	skyBoxShader = new Shader();
	skyBoxShader->createFromFiles("shaders/skybox.vs", "shaders/skybox.frag");

	uniformProjection = skyBoxShader->getProjectionLocation();
	uniformView = skyBoxShader->getViewLocation();
	skyBoxDay = skyBoxShader->getSkyBoxLocation();
	skyBoxNight = skyBoxShader->getSkyBox2Location();
	blendFactor = skyBoxShader->getBlendFactorLocation();

	// Texture Day setup
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, bitDepth;

	for (size_t i = 0; i < 6; i++)
	{
		unsigned char *textureData = stbi_load(faceLocations[i].c_str(), &width, &height, &bitDepth, 0);
		if (!textureData)
		{
			printf("Failed to find: %s\n", faceLocations[i].c_str());
			return;
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
		stbi_image_free(textureData);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	

	// Mesh Setup
	// Mesh Setup Code (to save you havin to type out the vertices of a cube!)
	float vertices[] =
	{
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Skybox::loadNightFaces(std::vector<std::string> nightFaceLocations) {
	// Night Texture Setup
	// Texture setup
//	glGenTextures(2, &textureNightID);
//	glBindTexture(GL_TEXTURE_CUBE_MAP, textureNightID);

	//int nightWidth, nightHeight, nightBitDepth;

	//for (size_t i = 0; i < 6; i++)
	//{
	//	unsigned char *textureDataX = stbi_load(nightFaceLocations[i].c_str(), &nightWidth, &nightHeight, &nightBitDepth, 0);
	//	if (!textureDataX)
	//	{
	//		printf("Failed to find: %s\n", nightFaceLocations[i].c_str());
	//		return;
	//	}
	//	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, nightWidth, nightHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, textureDataX);
	//	stbi_image_free(textureDataX);
	//}

	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Skybox::renderSkybox(GLfloat deltaTime, glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	 rotation += ROTATE_SPEED * 0.5f / 10.0f;

	 viewMatrix = glm::mat4(glm::mat3(viewMatrix));
	 viewMatrix = glm::rotate(viewMatrix, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));

	glDepthMask(GL_FALSE);

	skyBoxShader->useShader();
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureNightID);

	glUniform1f(blendFactor, 0.5f);
	glUniform1i(skyBoxDay, 0);
	glUniform1i(skyBoxNight, 1);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDeleteTextures(1, &textureID);
	glBindVertexArray(0);

	glDepthMask(GL_TRUE);
}

Skybox::~Skybox()
{
}
