#include "Camera.h"
#include <glm/gtx/transform2.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

auto X_UNIT = glm::vec3(1.0, 0.0, 0.0);
auto Y_UNIT = glm::vec3(0.0, 1.0, 0.0);

Camera::Camera(float screenWidth, float screenHeight)
	: target(0.0f, 0.0f, 0.0f)
	, screenWidth(screenWidth)
	, screenHeight(screenHeight)
	, zDistance(4.0)
	, yaw(45.0)
	, pitch(-15.0)
	, fov(60.0)
{
	// Calc position from rotation
	position = glm::vec3(0, 0, zDistance);
	glm::mat4 rotationMatrix(1.0);
	rotationMatrix *= glm::rotate(glm::radians(yaw), Y_UNIT);
	rotationMatrix *= glm::rotate(glm::radians(pitch), X_UNIT);
	position = glm::vec3(rotationMatrix * glm::vec4(position, 1.0));

	// Set View/Projection
	view = glm::lookAt(position, target, Y_UNIT);
	projection = glm::perspective(glm::radians(60.0f),
		screenWidth / screenHeight, 0.01f, 100.0f);
}

void Camera::Update()
{
	// Calc position from rotation
	position = glm::vec3(0, 0, zDistance);
	glm::mat4 rotationMatrix(1.0);
	rotationMatrix *= glm::rotate(glm::radians(yaw), Y_UNIT);
	rotationMatrix *= glm::rotate(glm::radians(pitch), X_UNIT);
	position = glm::vec3(rotationMatrix * glm::vec4(position, 1.0));

	// Calc View/Projection
	view = glm::lookAt(position, target, Y_UNIT);
	projection = glm::perspective(glm::radians(fov),
		screenWidth / screenHeight, 0.01f, 100.0f);
}
