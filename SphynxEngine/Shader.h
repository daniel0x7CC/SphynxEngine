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
	GLuint getScaleLocation();
	GLuint getHalfScaleLocation();
	GLuint getHalfTerrainSizeLocation();
	GLuint getMVPLocation();

	void useShader();
	void clearShader();

	~Shader();

private:
	GLuint shaderID, uniformProjection, uniformModel, uniformView;
	GLuint vVertex, heightMapTexture,
		scale, half_scale, HALF_TERRAIN_SIZE,
		MVP;

	void compileShader(const char* vertexCode, const char* fragmentCode);
	void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

