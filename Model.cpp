#include "Model.h"
#include "Shader.h"
#include "Mesh.h"

Model::Model()
	: modelMatrix(1.0f)
{
}

void Model::LoadQuad()
{
	Mesh* quad = new Mesh();
	quad->CreateQuads();
	meshes.push_back(quad);
}

void Model::Draw(Shader* shader)
{
	for (auto mesh : meshes) {
		mesh->Draw(shader);
	}
}
