#pragma once
#include <glm/glm.hpp>

class InputManager;

// Cameraはとりあえず原点中心の回転運動のみをAssum
class Camera
{
	friend InputManager;
public:
	Camera(const float screenWidth, const float screenHeight);

	void Update();

	auto GetViewProjection() const { return projection * view; }
	auto GetProjection() const { return projection; }
	auto GetView() const { return view; }
	auto GetPos() const { return position; }

private:
	glm::vec3 position;
	glm::vec3 target;

	glm::mat4 view;
	glm::mat4 projection;

	float screenWidth, screenHeight;
	float fov;
	float pitch, yaw, zDistance;
};

