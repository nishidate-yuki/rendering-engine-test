#include "Scene.h"
#include "Model.h"
#include <iostream>
#include "Importer.h"
#include "Camera.h"
#include "WindowManager.h"

Scene::Scene(Engine* engine)
	: meshShader(nullptr)
	, engine(engine)
{
	
}

Scene::~Scene()
{
}

bool Scene::Initialize(float screenWidth, float screenHeight)
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
	meshShader->SetActive();
	meshShader->SetMatrixUniform("uViewProj", camera->GetViewProjection());	// Camera
	for (auto model : models) {
		model->Draw(meshShader);
	}
}

void Scene::Update(float deltaTime)
{
	for (auto model : models) {
		model->Update(deltaTime);
	}
}


bool Scene::LoadContent()
{
	//Model* model = new Model();
	//model->LoadQuad();
	//models.push_back(model);

	//Model* model = Importer::ImportModel("Assets/bunny.fbx");
	//Model* model = Importer::ImportModel("Assets/Cube.fbx");
	//model->SetScale(glm::vec3(0.01f));
	Model* model = Importer::ImportModel("Assets/DamagedHelmet/glTF/DamagedHelmet.gltf");
	models.push_back(model);

	return true;
}

bool Scene::LoadShaders()
{
	meshShader = new Shader();
	if (!meshShader->Load("Shaders/Normal.vert", "Shaders/Normal.frag")) {
		return false;
	}
	meshShader->SetActive();
	return true;
}
