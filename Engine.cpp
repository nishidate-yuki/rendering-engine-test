#include "Engine.h"
#include <iostream>
#include <SDL2/SDL.h>
#include "Renderer.h"
#include "WindowManager.h"
#include "InputManager.h"

Engine::Engine()
	: isRunning(true)
	, scene(this)
{
	renderer = new Renderer(this);
	inputManager = new InputManager(this);
	windowManager = new WindowManager(this);
}

Engine::~Engine()
{
	delete windowManager;
	delete renderer;
	delete inputManager;
}

bool Engine::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	float screenWidth = 1024.0f;
	float screenHeight = 768.0f;

	// Initialize vars
	bool success = true;
	success &= windowManager->Initialize(screenWidth, screenHeight);
	success &= scene.Initialize(screenWidth, screenHeight);
	success &= renderer->Initialize(windowManager, &scene);
	success &= inputManager->Initialize(&scene);
	if (!success) {
		SDL_Log("Failed to initialize");
		return false;
	}

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
