#pragma once
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#define GLEW_STATIC
#include <GL/glew.h>

class Shader
{
public:
	Shader();

	void createFromString(const char* vertexCode, const char* fragmentCode);
	void createFromFiles(const char* vertexLocation, const char* fragmentLocation);

	std::string readFile(const char* fileLocation);

	GLuint getProjectionLocation();
	GLuint getModelLocation();
	GLuint getViewLocation();
	GLuint getVertexLocation();
	GLuint getHeightMapTextureLocation();
	GLuint getRTextureLocation();
	GLuint getGTextureLocation();
	GLuint getBTextureLocation();
	GLuint getMVPLocation();
	GLuint getBlendMapLocation();
	GLuint getBackgroundTextureLocation();
	GLuint getSkyBoxLocation();
	GLuint getSkyBox2Location();
	GLuint getBlendFactorLocation();

	void useShader();
	void clearShader();

	~Shader();

private:
	GLuint shaderID, uniformProjection, uniformModel, uniformView, blendMapLocation, bgTextureLocation, skyBoxLocation, skyBox2Location
		, blendFactorLocation;
	GLuint vVertex, heightMapTexture,
		MVP;
	GLuint rTextureLocation, gTextureLocation, bTextureLocation;
	void compileShader(const char* vertexCode, const char* fragmentCode);
	void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

