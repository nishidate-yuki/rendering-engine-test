#include "Scene.h"
#include "Mesh.h"
#include <iostream>

Scene::Scene()
{
}

void Scene::Draw(Shader* shader)
{
	for (auto mesh : meshes) {
		mesh->Draw(shader);
	}
}

void Scene::LoadContent()
{
	Mesh* quad = new Mesh();
	quad->CreateQuads();
	meshes.push_back(quad);
}
