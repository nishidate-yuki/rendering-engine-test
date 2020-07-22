#include "Scene.h"
#include <iostream>
#include "Model.h"
#include "Camera.h"
#include "Importer.h"
#include "WindowManager.h"

void CheckGLError(std::string str)
{
	GLenum err;
	while (err = glGetError()) {
		auto errString = gluErrorString(err);
		std::cout << str << ": " << err << errString;
	}
}

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
	// Update shader
	meshShader->SetActive();
	meshShader->SetMatrix("viewProj", camera->GetViewProjection());
	meshShader->SetDirectionalLight("uDirLight", dirLight);

	// Draw models
	for (auto model : models) {
		model->Draw(meshShader);
	}

	// Draw sky
	sky.Draw(camera->GetView(), camera->GetProjection());
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

	sky.Initialize("Assets/palermo_park_4k.hdr", engine);

	return true;
}

bool Scene::LoadShaders()
{
	meshShader = new Shader();
	// Normal, BasicMesh, Lambert, NormalMapping
	if (!meshShader->Load("Shaders/NormalMapping.vert", "Shaders/NormalMapping.frag")) {
		return false;
	}
	return true;
}
