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
	CheckGLError("Before Scene::Draw()");
	// Meshes
	meshShader->SetActive();
	meshShader->SetMatrix("uViewProj", camera->GetViewProjection());
	meshShader->SetDirectionalLight("uDirLight", dirLight);
	CheckGLError("SetupMeshShader");

	for (auto model : models) {
		model->Draw(meshShader);
	}
	CheckGLError("model->Draw(meshShader)");

	// Skybox
	//skyShader->SetActive();
	//skyShader->SetMatrix("uViewProj", camera->GetViewProjection());
	//sky.Draw(skyShader);
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

	CheckGLError("Before sky.Initialize");
	sky.Initialize("Assets/palermo_park_4k.hdr");
	CheckGLError("sky.Initialize");

	return true;
}

bool Scene::LoadShaders()
{
	meshShader = new Shader();
	// Normal, BasicMesh, Lambert, NormalMapping
	if (!meshShader->Load("Shaders/NormalMapping.vert", "Shaders/NormalMapping.frag")) {
		return false;
	}

	//skyShader = new Shader();
	//if (!skyShader->Load("Shaders/SkyShader.vert", "Shaders/SkyShader.frag")) {
	//	return false;
	//}
	return true;
}
//
//void Scene::SetupIBL()
//{
//	// Create Frame/Render buffer
//	glGenFramebuffers(1, &captureFBO);
//	glGenRenderbuffers(1, &captureRBO);
//
//	glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
//	glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
//
//	// Render bufferのメモリ割り当てを行う
//	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
//	// バインド中のFrame bufferにRender bufferをアタッチする
//	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, captureRBO);
//
//	// キューブマップカラーテクスチャを用意する
//	glGenTextures(1, &envCubemap);
//	glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
//	for (unsigned int i = 0; i < 6; ++i) {
//		// note that we store each face with 16 bit floating point values
//		// メモリ割り当てをするだけで、データは空にする
//		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F,
//			512, 512, 0, GL_RGB, GL_FLOAT, nullptr);
//	}
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	// VP行列を作成する
//	glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
//	glm::mat4 captureViews[] =
//	{
//	   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
//	   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
//	   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
//	   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
//	   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
//	   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
//	};
//
//	// convert HDR equirectangular environment map to cubemap equivalent
//	skyShader->SetActive();
//	skyShader->SetInt("skybox", 0);
//	// 専用のV/P行列が必要
//	skyShader->SetMatrix("projection", captureProjection);
//	sky.SetActive();
//	//glActiveTexture(GL_TEXTURE0);
//	//glBindTexture(GL_TEXTURE_2D, hdrTexture);
//
//
//
//	glViewport(0, 0, 512, 512); // don't forget to configure the viewport to the capture dimensions.
//	glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
//	for (unsigned int i = 0; i < 6; ++i) {
//
//		// Set View
//		skyShader->SetMatrix("view", captureViews[i]);
//
//		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
//			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, envCubemap, 0);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		// ここでレンダリングした画像をテクスチャに保存しておく
//		RenderCube(); // renders a 1x1 cube
//	}
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//}
//
//void Scene::RenderCube()
//{
//	// initialize (if necessary)
//	if (cubeVAO == 0) {
//		float vertices[] = {
//			// back face
//			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
//			1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
//			1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right
//			1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
//			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
//			-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
//			// front face
//			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
//			1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
//			1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
//			1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
//			-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
//			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
//			// left face
//			-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
//			-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
//			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
//			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
//			-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
//			-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
//			// right face
//			1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
//			1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
//			1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right
//			1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
//			1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
//			1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left
//			// bottom face
//			-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
//			1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
//			1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
//			1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
//			-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
//			-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
//			// top face
//			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
//			1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
//			1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right
//			1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
//			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
//			-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left
//		};
//		glGenVertexArrays(1, &cubeVAO);
//		glGenBuffers(1, &cubeVBO);
//		// fill buffer
//		glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//		// link vertex attributes
//		glBindVertexArray(cubeVAO);
//		glEnableVertexAttribArray(0);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//		glEnableVertexAttribArray(1);
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//		glEnableVertexAttribArray(2);
//		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//		glBindVertexArray(0);
//	}
//	// render Cube
//	glBindVertexArray(cubeVAO);
//	glDrawArrays(GL_TRIANGLES, 0, 36);
//	glBindVertexArray(0);
//}
