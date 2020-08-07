#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <unordered_map>
#include "Mesh.h"
class Shader;

class Model
{
	friend class Importer;	// Make meshes accessible
public:
	Model();
	~Model();

	void Update(const float deltaTime);
	void Draw(Shader* shader);
	void SetScale(const glm::vec3& scale);
	void SetScale(const float scale);
private:
	std::vector<Mesh*> meshes;
	glm::mat4 modelMatrix;
};
