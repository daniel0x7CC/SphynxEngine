#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "Skybox.h"
#include "Model.h"
#include "Terrain.h"
#include "TerrainTexture.h"

const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;
Camera camera;
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
Texture brickTexture, grassTexture;
Skybox skybox;
Model objLoader;
Terrain terrain;
TerrainTexture terrainTexture;
int frameCount = 0;


// Vertex Shader
static const char* vShader = "core.vs";

// Fragment Shader
static const char* fShader = "core.frag";

void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		// x     y     z	u		v
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 1.0f, 0.5f, 0.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.5f, 1.0f
	};

	Mesh *obj1 = new Mesh();
	obj1->createMesh(vertices, indices, 20, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->createMesh(vertices, indices, 20, 12);
	meshList.push_back(obj2);
}

void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->createFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

int main()
{
	mainWindow = Window(1280, 800);
	mainWindow.initialize();

	terrain = Terrain("heightmaps/sample2.png");

	CreateObjects();
	CreateShaders();
	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f);
	brickTexture = Texture("textures/dirt.png");
	brickTexture.loadTexture();

//	grassTexture = Texture("textures/grass.png");
//	grassTexture.loadTexture();

	terrainTexture = TerrainTexture("textures/dirt.png", "textures/path.png", "textures/mud.png", "textures/grass.png", "heightmaps/blendmap.png");
	terrainTexture.loadTextures();

	objLoader.loadObj("models/pikachu/Pikachu.obj");

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("textures/skybox_02/right.png");
	skyboxFaces.push_back("textures/skybox_02/left.png");
	skyboxFaces.push_back("textures/skybox_02/top.png");
	skyboxFaces.push_back("textures/skybox_02/bottom.png");
	skyboxFaces.push_back("textures/skybox_02/back.png");
	skyboxFaces.push_back("textures/skybox_02/front.png");

	std::vector<std::string> skyboxNightFaces;
	skyboxNightFaces.push_back("textures/night/right.png");
	skyboxNightFaces.push_back("textures/night/left.png");
	skyboxNightFaces.push_back("textures/night/top.png");
	skyboxNightFaces.push_back("textures/night/bottom.png");
	skyboxNightFaces.push_back("textures/night/back.png");
	skyboxNightFaces.push_back("textures/night/front.png");

	skybox = Skybox(skyboxFaces);
	skybox.loadNightFaces(skyboxNightFaces);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat) mainWindow.getBufferWidth() / (GLfloat) mainWindow.getBufferHeight(), 0.1f, 100.0f);

	// Loop until window closed
	while (!mainWindow.getShouldClose())
	{
		double now = glfwGetTime(); 
		deltaTime = now - lastTime;
		
		frameCount++;

		if (deltaTime >= 1.0) {
			mainWindow.setTitle(frameCount);
			printf("fps count: %d", frameCount);
			frameCount = 0;
			lastTime = now;
		}

		// Get + Handle User Input
		glfwPollEvents();

		camera.keyControl(mainWindow.getKeys(), deltaTime);
		//camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glViewport(0, 0, 1280, 800);

		glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		skybox.renderSkybox(deltaTime, camera.calculateViewMatrix(), projection);

		objLoader.render(camera.calculateViewMatrix(), projection);

		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectionLocation();
		uniformView = shaderList[0].getViewLocation();

		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));

		brickTexture.useTexture();
		meshList[0]->renderMesh();

		//grassTexture.useTexture();
		terrainTexture.bindTextures();
		terrain.renderFromHeightmap(camera.calculateViewMatrix(), projection);

		//model = glm::mat4();
		//model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//meshList[1]->renderMesh();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}