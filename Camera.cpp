#include "Camera.h"
#include <glm/gtx/transform2.hpp>

Camera::Camera(float screenWidth, float screenHeight)
	: position(2.0f, 0.0f, -4.0f)
	, target(0.0f, 0.0f, 0.0f)
{
	view = glm::lookAt(position, target, glm::vec3(0.0f, 1.0f, 0.0f));
	projection = glm::perspective(glm::radians(60.0f),
		screenWidth / screenHeight, 0.01f, 100.0f);
}
