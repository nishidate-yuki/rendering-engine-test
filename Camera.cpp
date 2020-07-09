#include "Camera.h"
#include <glm/gtx/transform2.hpp>

Camera::Camera(float screenWidth, float screenHeight)
{
	view = glm::lookAt(glm::vec3(4.0f, 4.0f, -4.0f),
		glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	projection = glm::perspective(glm::radians(45.0f),
		screenWidth / screenHeight, 0.01f, 100.0f);
}
