#include "Mesh.h"
#include "VertexArray.h"
#include "Shader.h"
#include <vector>

Mesh::Mesh()
{
	worldTransform = glm::mat4(1.0f);
}

Mesh::Mesh(std::vector<Vertex>& vertices,
		   std::vector<unsigned int>& indices)
{
	worldTransform = glm::mat4(1.0f);
	vertexArray = new VertexArray(&vertices[0], vertices.size(), &indices[0], indices.size());
}

void Mesh::Draw(Shader* shader)
{
	shader->SetMatrixUniform("uWorldTransform", worldTransform);
	vertexArray->SetActive();
	glDrawElements(GL_TRIANGLES,
		vertexArray->GetNumIndices(), 
		GL_UNSIGNED_INT, nullptr);
}

void Mesh::CreateQuads()
{
	float size = 1.0f;
	// pos, nor, tex
	//float vertices[] = {
	//	-size, size, 0.f, 0.f, 0.f, 1.0f, 0.f, 0.f, // top left
	//	size, size, 0.f, 0.f, 0.f, 1.0f, 1.f, 0.f, // top right
	//	size,-size, 0.f, 0.f, 0.f, 1.0f, 1.f, 1.f, // bottom right
	//	-size,-size, 0.f, 0.f, 0.f, 1.0f, 0.f, 1.f  // bottom left
	//};

	std::vector<Vertex> vertices = {
		{glm::vec3(-size, size, 0.f), glm::vec3(0.f, 0.f, 1.0f), glm::vec2(0.f, 0.f)}, // top left
		{glm::vec3(size, size, 0.f),  glm::vec3(0.f, 0.f, 1.0f), glm::vec2(1.f, 0.f)}, // top right
		{glm::vec3(size,-size, 0.f),  glm::vec3(0.f, 0.f, 1.0f), glm::vec2(1.f, 1.f)}, // bottom right
		{glm::vec3(-size,-size, 0.f), glm::vec3(0.f, 0.f, 1.0f), glm::vec2(0.f, 1.f)}  // bottom left
	};

	std::vector<unsigned int> indices = {
		0, 1, 2,
		2, 3, 0
	};

	//unsigned int indices[] = {
	//	0, 1, 2,
	//	2, 3, 0
	//};

	vertexArray = new VertexArray(&vertices[0], 4, &indices[0], 6);
}
