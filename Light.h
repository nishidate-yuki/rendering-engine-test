#pragma once
#include <glm/glm.hpp>

struct DirectionalLight
{
	glm::vec3 color = glm::vec3(1.0f);
	float intensity = 1.0f;
	glm::vec3 direction = glm::vec3(-1.0f);
};

struct PointLight
{
	glm::vec3 color = glm::vec3(1.0f);
	float intensity = 1.0f;
	glm::vec3 position = glm::vec3(0.0f);
};