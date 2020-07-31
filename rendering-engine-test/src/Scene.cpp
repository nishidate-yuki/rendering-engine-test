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

	if (!LoadContent(Content::Helmet)) {
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
	meshShader->SetVector("camPos", camera->GetPos());
	meshShader->SetFloat("time", float(time++));

	// Set irradiance map
	meshShader->SetInt("irradianceMap", 16);
	glActiveTexture(GL_TEXTURE16);
	glBindTexture(GL_TEXTURE_CUBE_MAP, sky.GetIrradianceMap());

	// Set env cubemap
	meshShader->SetInt("envCubemap", 17);
	glActiveTexture(GL_TEXTURE17);
	glBindTexture(GL_TEXTURE_CUBE_MAP, sky.GetEnvCubemap());

	// Set prefilterMap
	meshShader->SetInt("prefilterMap", 18);
	glActiveTexture(GL_TEXTURE18);
	glBindTexture(GL_TEXTURE_CUBE_MAP, sky.GetPrefilterMap());

	// Set prefilterMap
	meshShader->SetInt("brdfLUT", 19);
	glActiveTexture(GL_TEXTURE19);
	glBindTexture(GL_TEXTURE_2D, sky.GetBrdfLUT());

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


bool Scene::LoadContent(Content cont)
{
	if (cont == Content::Helmet) {
		Model* model = Importer::ImportModel("Assets/DamagedHelmet/glTF/DamagedHelmet.gltf");
		models.push_back(model);
	}
	else if (cont == Content::Spheres) {
		// Load spheres
	}

	//sky.Initialize("Assets/PaperMill_E_3k.hdr", engine);
	sky.Initialize("Assets/palermo_park_4k.hdr", engine);
	//sky.Initialize("Assets/the_sky_is_on_fire_4k.hdr", engine);

	return true;
}

bool Scene::LoadShaders()
{
	meshShader = new Shader();
	// Normal, BasicMesh, Lambert, NormalMapping, DiffuseIBL, PBR, SpecularIBL
	if (!meshShader->Load("Shaders/PBR.vert", "Shaders/PBR.frag")) {
		return false;
	}
	return true;
}
