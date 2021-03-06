#include "Shader.h"

Shader::Shader()
{
	shaderID = 0;
	uniformModel = 0;
	uniformProjection = 0;
}

void Shader::createFromString(const char* vertexCode, const char* fragmentCode)
{
	compileShader(vertexCode, fragmentCode);
}

void Shader::createFromFiles(const char* vertexLocation, const char* fragmentLocation)
{
	std::string vertexString = readFile(vertexLocation);
	std::string fragmentString = readFile(fragmentLocation);
	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	compileShader(vertexCode, fragmentCode);
}

std::string Shader::readFile(const char* fileLocation)
{
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open()) {
		printf("Failed to read %s! File doesn't exist.", fileLocation);
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

void Shader::compileShader(const char* vertexCode, const char* fragmentCode)
{
	shaderID = glCreateProgram();

	if (!shaderID)
	{
		printf("Error creating shader program!\n");
		return;
	}

	addShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	addShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}

	uniformProjection = glGetUniformLocation(shaderID, "projection");
	uniformModel = glGetUniformLocation(shaderID, "model");
	uniformView = glGetUniformLocation(shaderID, "view");
	// uniforms for terrain loading
	vVertex = glGetUniformLocation(shaderID, "vVertex");
	heightMapTexture = glGetUniformLocation(shaderID, "vVertex");

	MVP = glGetUniformLocation(shaderID, "MVP");

	bgTextureLocation = glGetUniformLocation(shaderID, "mTexture");
	rTextureLocation = glGetUniformLocation(shaderID, "rTexture");
	gTextureLocation = glGetUniformLocation(shaderID, "gTexture");
	bTextureLocation = glGetUniformLocation(shaderID, "bTexture");
	blendMapLocation = glGetUniformLocation(shaderID, "blendMap");

	skyBoxLocation = glGetUniformLocation(shaderID, "skybox");

	skyBox2Location = glGetUniformLocation(shaderID, "skyboxNight");

	blendFactorLocation = glGetUniformLocation(shaderID, "blendFactor");
}

GLuint Shader::getSkyBoxLocation()
{
	return skyBoxLocation;
}

GLuint Shader::getSkyBox2Location()
{
	return skyBox2Location;
}

GLuint Shader::getBlendFactorLocation()
{
	return blendFactorLocation;
}

GLuint Shader::getBackgroundTextureLocation()
{
	return bgTextureLocation;
}

GLuint Shader::getBlendMapLocation()
{
	return blendMapLocation;
}

GLuint Shader::getProjectionLocation()
{
	return uniformProjection;
}
GLuint Shader::getModelLocation()
{
	return uniformModel;
}
GLuint Shader::getViewLocation()
{
	return uniformView;
}
GLuint Shader::getVertexLocation()
{
	return vVertex;
}
GLuint Shader::getHeightMapTextureLocation()
{
	return heightMapTexture;
}
GLuint Shader::getRTextureLocation()
{
	return rTextureLocation;
}
GLuint Shader::getGTextureLocation()
{
	return gTextureLocation;
}
GLuint Shader::getBTextureLocation()
{
	return bTextureLocation;
}
GLuint Shader::getMVPLocation()
{
	return MVP;
}

void Shader::useShader()
{
	glUseProgram(shaderID);
}

void Shader::clearShader()
{
	if (shaderID != 0)
	{
		glDeleteProgram(shaderID);
		shaderID = 0;
	}

	uniformModel = 0;
	uniformProjection = 0;
}


void Shader::addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
}

Shader::~Shader()
{
	clearShader();
}
