#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

enum class Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
};

class Camera {
public:
	//Camera attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	// Euler Angels
	float Yaw;
	float Pitch;
	//Camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	//
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		float yaw = -90.0f,
		float pitch = 0.0f);

	//Returns view matrix using Euler Angles and the LookAt Matrix
	glm::mat4 getViewMatrix();

	//Process input recieved from any keyboard-like input system
	void processKeyboard(Camera_Movement direction, float deltaTime);

	//Process input from mouse
	void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

private:
	void updateCameraVectors();

};