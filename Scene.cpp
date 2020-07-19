#include "Scene.h"
#include <iostream>
#include "Model.h"
#include "Camera.h"
#include "Importer.h"
#include "WindowManager.h"

Scene::Scene(Engine* engine)
	: meshShader(nullptr)
	, engine(engine)
{
}

Scene::~Scene()
{
	while (!models.empty()) {
		delete models.back();
	}
	meshShader->Unload();
	delete meshShader;
	delete camera;
}

bool Scene::Initialize(const float screenWidth, const float screenHeight)
{
	camera = new Camera(screenWidth, screenHeight);

	if (!LoadContent()) {
		printf("Failed to load contents.\n");
		return false;
	}

	if (!LoadShaders()) {
		printf("Failed to load shaders.\n");
		return false;
	}
}

void Scene::Draw()
{
	// Meshes
	meshShader->SetActive();
	meshShader->SetMatrix("uViewProj", camera->GetViewProjection());
	meshShader->SetDirectionalLight("uDirLight", dirLight);

	for (auto model : models) {
		model->Draw(meshShader);
	}

	// Skybox
	skyShader->SetActive();
	skyShader->SetMatrix("uViewProj", camera->GetViewProjection());
	sky.Draw(skyShader);
}

void Scene::Update(const float deltaTime)
{
	for (auto model : models) {
		model->Update(deltaTime);
	}
}


bool Scene::LoadContent()
{
	Model* model = Importer::ImportModel("Assets/DamagedHelmet/glTF/DamagedHelmet.gltf");
	models.push_back(model);

	sky.Initialize("Assets/palermo_park_4k.hdr");
	return true;
}

bool Scene::LoadShaders()
{
	meshShader = new Shader();
	// Normal, BasicMesh, Lambert, NormalMapping
	if (!meshShader->Load("Shaders/NormalMapping.vert", "Shaders/NormalMapping.frag")) {
		return false;
	}

	skyShader = new Shader();
	if (!skyShader->Load("Shaders/SkyShader.vert", "Shaders/SkyShader.frag")) {
		return false;
	}
	return true;
}
