#include "InputManager.h"
#include "Camera.h"
#include "Scene.h"
#include "Engine.h"

//
//bool KeyboardState::GetKeyValue(SDL_Scancode keyCode) const
//{
//	return currState[keyCode] == 1;
//}
//
//ButtonState KeyboardState::GetKeyState(SDL_Scancode keyCode) const
//{
//	if (prevState[keyCode] == 0) {
//		if (currState[keyCode] == 0) {
//			return ENone;		// 0->0
//		} else {
//			return EPressed;	// 0->1
//		}
//	} else // Prev state must be 1
//	{
//		if (currState[keyCode] == 0) {
//			return EReleased;	// 1->0
//		} else {
//			return EHeld;		// 1->1
//		}
//	}
//}
//
//bool MouseState::GetButtonValue(int button) const
//{
//	return (SDL_BUTTON(button) & currButtons) == 1;
//}
//
//ButtonState MouseState::GetButtonState(int button) const
//{
//	int mask = SDL_BUTTON(button);
//	if ((mask & prevButtons) == 0) {
//		if ((mask & currButtons) == 0) {
//			return ENone;		// 0->0
//		} else {
//			return EPressed;	// 0->1
//		}
//	} else {
//		if ((mask & currButtons) == 0) {
//			return EReleased;	// 1->0
//		} else {
//			return EHeld;		// 1->1
//		}
//	}
//}

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

	//// Keyboard
	//keyboardState.currState = SDL_GetKeyboardState(NULL);
	//memset(keyboardState.prevState, 0, SDL_NUM_SCANCODES);	// Clear prev state

	//// Mouse
	//mouseState.currButtons = 0;
	//mouseState.prevButtons = 0;

	return true;
}

void InputManager::Shutdown()
{
}

void InputManager::ProcessInput()
{
	// Mouse
	//int x = 0, y = 0;
	//if (mouseState.isRelative) {
	//	mouseState.currButtons = SDL_GetRelativeMouseState(&x, &y);
	//} else {
	//	mouseState.currButtons = SDL_GetMouseState(&x, &y);
	//}
	//mouseState.mousePos.x = static_cast<float>(x);
	//mouseState.mousePos.y = static_cast<float>(y);

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		// Quit
		switch (event.type) {
			case SDL_QUIT:
				engine->Stop();
				break;
		}
	}
}

void InputManager::ProcessEvent(const SDL_Event& event)
{
	//if (event.type == SDL_MOUSEMOTION) {
	//	//Only move camera if the left button is pressed
	//	if (event.motion.state & SDL_BUTTON_LMASK) {
	//		//While left button is pressed change mouse to relative mode
	//		SDL_SetRelativeMouseMode(SDL_TRUE);

	//		float sens = sceneCamera->mouseSens;
	//		float xOffset = (float)event->motion.xrel * sens;
	//		float yOffset = -(float)event->motion.yrel * sens;

	//		//To reduce precision issues we keep the yaw constrained to 360 degrees
	//		sceneCamera->yaw = glm::mod(sceneCamera->yaw + xOffset, 360.0f);
	//		sceneCamera->pitch += yOffset;

	//		//Limiting the range of the pitch to avoid flips
	//		if (sceneCamera->pitch > 89.0f) {
	//			sceneCamera->pitch = 89.0f;
	//		} else if (sceneCamera->pitch < -89.0f) {
	//			sceneCamera->pitch = -89.0f;
	//		}
	//	} else {
	//		//Once the left butto is not pressed set the mouse to normal mode
	//		SDL_SetRelativeMouseMode(SDL_FALSE);
	//	}
	//}
}

//void InputManager::SetRelativeMouseMode(bool value)
//{
//	SDL_bool set = value ? SDL_TRUE : SDL_FALSE;
//	SDL_SetRelativeMouseMode(set);
//
//	mouseState.isRelative = value;
//}
