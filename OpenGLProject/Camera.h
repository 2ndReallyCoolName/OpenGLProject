#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <glm/gtc/quaternion.hpp>


enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
public:
	Camera(float mouseSensitivity = 0.1f, float movementSpeed=4.5f, float scrollSensitivity = 3.5f)
		: sensitivity(mouseSensitivity), movementSpeed(movementSpeed), scrollSensitivity(scrollSensitivity) {

		updateVectors();

	}

	void processKeyboar(Camera_Movement movement, float deltaTime) {
		float cameraSpeed = movementSpeed * deltaTime;

		glm::quat qf = orientation * glm::quat(0, 0, 0, -1) * glm::conjugate(orientation);
		glm::vec3 front = { qf.x, qf.y, qf.z };
		glm::vec3 right = glm::normalize(glm::cross(front, worldUp));

		switch (movement) {
		case FORWARD:
			cameraPos += front * cameraSpeed;
			break;
		case BACKWARD:
			cameraPos -= front * cameraSpeed;
			break;
		case LEFT:
			cameraPos -= right * cameraSpeed;
			break;
		case RIGHT:
			cameraPos += right * cameraSpeed;
			break;
		}

		cameraPos.y = 0.0f;
	}

	void processMouse(float xoffset, float yoffset, GLboolean constrainPitch = true) {
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		rightAngle += xoffset;
		upAngle += yoffset;

		updateVectors();
	}

	void updateVectors() {
		glm::quat aroundY = glm::angleAxis(glm::radians(-rightAngle), worldUp);
		glm::quat aroundX = glm::angleAxis(glm::radians(upAngle), worldRight);
		orientation = aroundY * aroundX;
	}

	void processScroll(float yoffset) {
		if (fov >= 1.0f && fov <= 45.0f)
			fov -= (float)yoffset * scrollSensitivity;
		if (fov <= 1.0f)
			fov = 1.0f;
		if (fov >= 45.0f)
			fov = 45.0f;
	}

	glm::mat4 GetViewMatrix()
	{
		glm::quat quatConj = glm::conjugate(orientation);
		glm::mat4 rotMat = glm::mat4_cast(quatConj);
		glm::mat4 transMat = glm::translate(glm::mat4(1.0f), -cameraPos);
		return rotMat * transMat;
	}

	float getFov() {
		return fov;
	}

private:

	float sensitivity;
	float scrollSensitivity;
	float movementSpeed;

	float fov = 45.0f;

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 worldRight = glm::vec3(1.0f, 0.0f, 0.0f);

	glm::quat orientation = glm::quat(0, 0, 0, -1);
	float rightAngle = 0.0f;
	float upAngle = 0.0f;
};