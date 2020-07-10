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
	, meshShader(nullptr)
{
}

Renderer::Renderer(Engine* engine, WindowManager* windowManager)
	: engine(engine)
	, meshShader(nullptr)
	, windowManager(windowManager)
{
}

Renderer::~Renderer()
{
}

bool Renderer::Initialize(float screenWidth, float screenHeight)
{
	//this->screenWidth = screenWidth;
	//this->screenHeight = screenHeight;

	//// Set OpenGL attributes
	//// Use the core OpenGL profile
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//// Specify version 3.3
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	//// Request a color buffer with 8-bits per RGBA channel
	//SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	//SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	//SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	//SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	//SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	//// Enable double buffering
	//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//// Antialiasing
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	//// Force OpenGL to use hardware acceleration
	//SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	//window = SDL_CreateWindow("GameTemplate", 100, 100,
	//	static_cast<int>(screenWidth), static_cast<int>(screenHeight), SDL_WINDOW_OPENGL);
	//if (!window) {
	//	SDL_Log("Failed to create window: %s", SDL_GetError());
	//	return false;
	//}

	//// Create an OpenGL context
	//context = SDL_GL_CreateContext(window);

	//// Initialize GLEW
	//glewExperimental = GL_TRUE;
	//if (glewInit() != GLEW_OK) {
	//	SDL_Log("Failed to initialize GLEW.");
	//	return false;
	//}

	//// On some platforms, GLEW will emit a benign error code,
	//// so clear it
	//glGetError();

	// Make sure we can create/compile shaders
	if (!LoadShaders()) {
		SDL_Log("Failed to load shaders.");
		return false;
	}

	scene = new Scene();
	scene->LoadContent();

	camera = new Camera(screenWidth, screenHeight);

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
	
	meshShader->SetActive();
	meshShader->SetMatrixUniform("uViewProj", camera->GetViewProjection());
	
	// Update lighting uniforms
	//SetLightUniforms(meshShader);

	// Draw scene
	scene->Draw(meshShader);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	// ----- “§‰ß•¨‘Ì‚ÌƒŒƒ“ƒ_ƒŠƒ“ƒO -----
	// pass
	// ----------------------------

	// Swap
	//SDL_GL_SwapWindow(window);
	windowManager->SwapWindow();
}

bool Renderer::LoadShaders()
{
	// Create basic mesh shader
	meshShader = new Shader();
	//if (!meshShader->Load("Shaders/BasicMesh.vert", "Shaders/BasicMesh.frag")) {
	//	return false;
	//}
	if (!meshShader->Load("Shaders/Normal.vert", "Shaders/Normal.frag")) {
		return false;
	}

	meshShader->SetActive();

	return true;
}
