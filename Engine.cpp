#include "Engine.h"
#include <iostream>
#include <SDL2/SDL.h>
#include "Renderer.h"
#include "WindowManager.h"
#include "InputManager.h"

Engine::Engine()
	: renderer(nullptr)
	, isRunning(true)
	, scene(this)
{
}

Engine::~Engine()
{
}

bool Engine::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	float screenWidth = 1024.0f;
	float screenHeight = 768.0f;

	// Create window manager
	windowManager = new WindowManager(this);
	if (!windowManager->Initialize(screenWidth, screenHeight)) {
		SDL_Log("Failed to initialize window manager");
		return false;
	}

	// Initialize scene
	scene.Initialize(screenWidth, screenHeight);

	// Create renderer
	renderer = new Renderer(this);
	renderer->Initialize(windowManager, &scene);

	// Create InputManager
	inputManager = new InputManager(this);
	inputManager->Initialize(&scene);

	ticksCount = SDL_GetTicks();

	return true;
}

void Engine::RunLoop()
{
	while (isRunning) {
		ProcessInput();
		Update();
		Render();
	}
}

void Engine::Shutdown()
{
}

void Engine::ProcessInput()
{
	inputManager->ProcessInput();
}

void Engine::Update()
{
	// 16msŒo‚Â‚Ü‚Å‘Ò‚Â
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16)) {
		// pass
	}
	float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;
	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}
	ticksCount = SDL_GetTicks();

	scene.Update(deltaTime);
}

void Engine::Render()
{
	renderer->Draw();
}

void Engine::LoadData()
{
}
