#pragma once
#include <glm/glm.hpp>

class InputManager;

// Camera�͂Ƃ肠�������_���S�̉�]�^���݂̂�Assum
class Camera
{
	friend InputManager;
public:
	Camera(float screenWidth, float screenHeight);

	void Update();

	// PV
	auto GetViewProjection() { return projection * view; }

private:
	glm::vec3 position;
	glm::vec3 target;

	glm::mat4 view;
	glm::mat4 projection;

	float screenWidth, screenHeight;

	float pitch, yaw, zDistance;
};

