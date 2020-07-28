#include "InputManager.h"
#include "Camera.h"
#include "Scene.h"
#include "Engine.h"
#include <iostream>

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
			case SDL_MOUSEMOTION:
				if (event.motion.state & SDL_BUTTON_LMASK) {
					float rotationSpeed = 0.25;
					float xOffset = -(float)event.motion.xrel * rotationSpeed;
					float yOffset = -(float)event.motion.yrel * rotationSpeed;

					// 360度に制限する
					camera->yaw = glm::mod(camera->yaw + xOffset, 360.0f);
					camera->pitch += yOffset;

					// フリップ回避のためにリミットを掛ける
					if (camera->pitch > 89.0f) {
						camera->pitch = 89.0f;
					} else if (camera->pitch < -89.0f) {
						camera->pitch = -89.0f;
					}

					camera->Update();
				}
				break;
			case SDL_MOUSEWHEEL:
				if (event.wheel.y > 0) { // scroll up
					camera->zDistance -= 0.5;
				} else if (event.wheel.y < 0) { // scroll down
					camera->zDistance += 0.5;
				}
				camera->Update();
		}
	}
}
