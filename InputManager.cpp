#include "InputManager.h"
#include "Camera.h"
#include "Scene.h"
#include "Engine.h"

InputManager::InputManager(Engine* engine)
	: engine(engine)
{
}

InputManager::~InputManager()
{
}

bool InputManager::Initialize(Scene* scene)
{
	this->scene = scene;
	this->camera = scene->GetCamera();
	return true;
}

void InputManager::Shutdown()
{
}

void InputManager::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				engine->Stop();
				break;
		}
	}
}
