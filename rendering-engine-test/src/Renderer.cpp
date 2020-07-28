#include "Renderer.h"
#include <iostream>
#include <GL/glew.h>
#include <glm/gtx/transform2.hpp>
#include "Shader.h"
#include "VertexArray.h"
#include "Scene.h"
#include "Camera.h"
#include "WindowManager.h"

Renderer::Renderer(Engine* engine)
	: engine(engine)
	, scene(nullptr)
	, camera(nullptr)
{
}

Renderer::~Renderer()
{
}

bool Renderer::Initialize(WindowManager* windowManager, Scene* scene)
{
	this->windowManager = windowManager;
	this->scene = scene;
	return true;
}

void Renderer::Shutdown()
{
}

void Renderer::UnloadData()
{
}

void Renderer::Draw()
{
	// Clear
	glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	
	scene->Draw();

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	// ----- “§‰ß•¨‘Ì‚ÌƒŒƒ“ƒ_ƒŠƒ“ƒO -----
	// pass
	// ----------------------------

	// Swap
	windowManager->SwapWindow();
}

