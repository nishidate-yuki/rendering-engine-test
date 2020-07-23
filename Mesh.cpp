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
	static const char* maps[] = {
		"albedoMap", "emissiveMap", "normalMap",
		"AOMap", "metalRoughMap"
	};

	for (int i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
			textures[i].SetActive();
			shader->SetInt(maps[i], i);
	}

	vertexArray->Draw();
}
