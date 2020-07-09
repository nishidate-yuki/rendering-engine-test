#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	Camera(float screenWidth, float screenHeight);

	auto GetViewProjection() { return projection * view; }

private:
	glm::vec3 position;
	glm::vec3 target;

	glm::mat4 view;
	glm::mat4 projection;
};

