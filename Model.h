#pragma once 
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <unordered_map>

class Mesh;
class Shader;

class Model
{
public:
	Model();

	void Update(float deltaTime);
	void Draw(Shader* shader);

	std::vector<Mesh*> meshes;

	void SetScale(const glm::vec3& scale);

private:
	glm::mat4 modelMatrix;

	//To avoid textures being loaded from disk more than once they are indexed into a dictionary
	//std::unordered_map<std::string, Texture> textureAtlas;
	//std::string directory, fileExtension;
};
