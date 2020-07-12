#include "InputManager.h"
#include "Camera.h"
#include "Scene.h"
#include "Engine.h"


bool KeyboardState::GetKeyValue(SDL_Scancode keyCode) const
{
	return currState[keyCode] == 1;
}

ButtonState KeyboardState::GetKeyState(SDL_Scancode keyCode) const
{
	if (prevState[keyCode] == 0) {
		if (currState[keyCode] == 0) {
			return ENone;		// 0->0
		} else {
			return EPressed;	// 0->1
		}
	} else // Prev state must be 1
	{
		if (currState[keyCode] == 0) {
			return EReleased;	// 1->0
		} else {
			return EHeld;		// 1->1
		}
	}
}

bool MouseState::GetButtonValue(int button) const
{
	return (SDL_BUTTON(button) & currButtons) == 1;
}

ButtonState MouseState::GetButtonState(int button) const
{
	int mask = SDL_BUTTON(button);
	if ((mask & prevButtons) == 0) {
		if ((mask & currButtons) == 0) {
			return ENone;
		} else {
			return EPressed;
		}
	} else {
		if ((mask & currButtons) == 0) {
			return EReleased;
		} else {
			return EHeld;
		}
	}
}

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
