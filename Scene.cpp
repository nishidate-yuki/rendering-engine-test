#include "Scene.h"
#include "Model.h"
#include <iostream>
#include "Importer.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Draw(Shader* shader)
{
	for (auto model : models) {
		model->Draw(shader);
	}
}

void Scene::LoadContent()
{
	//Model* model = new Model();
	//model->LoadQuad();
	//models.push_back(model);

	Model* bunny = Importer::ImportModel("Assets/bunny.fbx");
	models.push_back(bunny);
}
