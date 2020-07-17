#pragma once
#include <string>
#include <vector>
#include "glm/glm.hpp"
#include "Texture.h"

class VertexArray;
class Shader;
class Texture;

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 tangent;
	glm::vec3 biTangent;
	glm::vec2 texCoords;
};

class Mesh
{
public:
	Mesh(const std::vector<Vertex>& vertices,
		const std::vector<unsigned int>& indices,
		const std::vector<Texture>& textures);

	void Draw(Shader* shader);

private:
	VertexArray* vertexArray;
	std::vector<Texture> textures;

	//std::string shaderName;
};

