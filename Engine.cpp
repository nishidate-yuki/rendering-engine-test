#include "Engine.h"
#include <iostream>
#include <SDL2/SDL.h>
#include "Renderer.h"
#include "WindowManager.h"
#include "Scene.h"

Engine::Engine()
	: renderer(nullptr)
	, isRunning(true)
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

	//Create scene
	scene = new Scene(this);
	scene->Initialize(screenWidth, screenHeight);

	// Create renderer
	renderer = new Renderer(this);
	renderer->Initialize(windowManager, scene);

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
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
		}
	}
}

void Engine::Update()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16)) {
		// pass
	}

	ticksCount = SDL_GetTicks();
}

void Engine::Render()
{
	renderer->Draw();
}

void Engine::LoadData()
{
}
