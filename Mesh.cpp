#include "Mesh.h"
#include "VertexArray.h"
#include "Shader.h"
#include <vector>

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures)
{
	vertexArray = new VertexArray(&vertices[0], vertices.size(), &indices[0], indices.size());
	this->textures = textures;
}

void Mesh::Draw(Shader* shader)
{
	vertexArray->SetActive();

	textures[0].SetActive();	// Diffuse

	glDrawElements(GL_TRIANGLES,
		vertexArray->GetNumIndices(), 
		GL_UNSIGNED_INT, nullptr);
}
