#pragma once
#include <string>
#include <vector>
#include "glm/glm.hpp"

class VertexArray;
class Shader;

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	//glm::vec3 tangent;
	//glm::vec3 biTangent;
	glm::vec2 texCoords;
};

class Mesh
{
public:
	Mesh();
	Mesh(std::vector<Vertex>& vertices,
		 std::vector<unsigned int>& indices);

	void Draw(Shader* shader);

	auto GetWorldTransform() { return worldTransform; };

	void CreateQuads();

private:
	VertexArray* vertexArray;

	//std::string shaderName;

	glm::mat4 worldTransform;

};

