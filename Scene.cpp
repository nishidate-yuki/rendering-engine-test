#include "Scene.h"
#include "Mesh.h"
#include "Model.h"
#include <iostream>

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Draw(Shader* shader)
{
	//for (auto mesh : meshes) {
	//	mesh->Draw(shader);
	//}

	for (auto model : models) {
		model->Draw(shader);
	}
}

void Scene::LoadContent()
{
	//Mesh* quad = new Mesh();
	//quad->CreateQuads();
	//meshes.push_back(quad);

	Model* model = new Model();
	model->LoadQuad();
	models.push_back(model);
}
