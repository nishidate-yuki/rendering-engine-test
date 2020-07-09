#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	Camera(float screenWidth, float screenHeight);

	auto GetViewProjection() { return projection * view; }

private:
	// View/projection for 3D shaders
	glm::mat4 view;
	glm::mat4 projection;
};

