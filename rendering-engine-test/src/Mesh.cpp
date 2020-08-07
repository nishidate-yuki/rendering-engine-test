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

	shader->SetInt("enableAO", 0);
	shader->SetInt("enableEmissive", 0);

	for (int i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		textures[i].SetActive();
		TextureType type = textures[i].GetType();
		if (type == TextureType::AmbientOcclusion) {
			shader->SetInt("enableAO", 1);
		}
		if (type == TextureType::Emissive) {
			shader->SetInt("enableEmissive", 1);
		}
		int typei = static_cast<int>(type);
		shader->SetInt(maps[typei], i);
	}

	vertexArray->Draw();
}
