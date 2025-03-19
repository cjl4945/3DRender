#include "Camera.h"
#include <gtc/constants.hpp>


Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
	: Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(4.5f),
	MouseSensitivity(0.1f), Zoom(45.0f)
{
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

//Returns view matrix using Euler Angles and the LookAt Matrix
glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(Position, Position + Front, Up);
}

//Process input recieved from any keyboard-like input system
void Camera::processKeyboard(Camera_Movement direction, float deltaTime, const Room& room)
{
	float velocity = MovementSpeed * deltaTime;
	glm::vec3 newPosition = Position;

	if (direction == Camera_Movement::FORWARD)
		{
			newPosition += Front * velocity;
		}
	if (direction == Camera_Movement::BACKWARD)
		{
			newPosition -= Front * velocity;
		}
	if (direction == Camera_Movement::LEFT)
		{
			newPosition -= Right * velocity;
		}
	if (direction == Camera_Movement::RIGHT)
		{
			newPosition += Right * velocity;
		}

	newPosition.x = glm::clamp(newPosition.x, room.minBounds.x, room.maxBounds.x);
	newPosition.y = glm::clamp(newPosition.y, room.minBounds.y, room.maxBounds.y);
	newPosition.z = glm::clamp(newPosition.z, room.minBounds.z, room.maxBounds.z);

	Position = newPosition;
		
}



//Process input from mouse
void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}
	updateCameraVectors();
}

void Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);
	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}