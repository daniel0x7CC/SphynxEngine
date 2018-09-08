#pragma once

#include <GL\glew.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>

#include <GLFW\glfw3.h>

class Camera
{
public:
	Camera();
	Camera(glm::vec3 initialPosition, glm::vec3 initialUp, GLfloat initialYaw, GLfloat initialPitch, GLfloat initialTurnSpeed, GLfloat initialMoveSpeed);
	
	void keyControl(bool* keys, GLfloat deltaTime);
	void mouseControl(GLfloat xChange, GLfloat yChange);


	glm::mat4 calculateViewMatrix();

	~Camera();

private:
	glm::vec3 position; // position of the camera
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat yaw; // rotate to x axis (left and right)
	GLfloat pitch; // rotate to y axis (up and down)

	GLfloat moveSpeed;
	GLfloat turnSpeed;

	void update();
};

