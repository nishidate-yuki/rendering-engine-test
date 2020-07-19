#include "Mesh.h"
#include "VertexArray.h"
#include "Shader.h"
#include <vector>

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures)
{
	vertexArray = new VertexArray(&vertices[0], vertices.size(), &indices[0], indices.size());
	this->textures = textures;
}

Mesh::Mesh(const float* vertices)
{
}

Mesh::~Mesh()
{
	delete(vertexArray);
}

void Mesh::Draw(Shader* shader)
{
	//textures[0].SetActive();

	if (textures.size() >= 1) {
		// Diffuse
		glActiveTexture(GL_TEXTURE0);
		textures[0].SetActive();
		shader->SetInt("uDiffuse", 0);
	}

	if (textures.size() >= 2) {
		// Emissive
		glActiveTexture(GL_TEXTURE1);
		textures[1].SetActive();
		shader->SetInt("uEmissiveMap", 1);
	}

	if (textures.size() >= 3) {
		// Normal
		glActiveTexture(GL_TEXTURE2);
		textures[2].SetActive();
		shader->SetInt("uNormalMap", 2);
	}

	vertexArray->Draw();
}
