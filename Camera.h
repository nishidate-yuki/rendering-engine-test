#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	Camera(float screenWidth, float screenHeight);

	// PV
	auto GetViewProjection() { return projection * view; }
	// VP
	//auto GetViewProjection() { return view * projection; }

private:
	glm::vec3 position;
	glm::vec3 target;

	glm::mat4 view;
	glm::mat4 projection;
};

