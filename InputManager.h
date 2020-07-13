#pragma once
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class Scene;
class Engine;
class Camera;
class InputManager;
//
//enum ButtonState
//{
//	ENone,
//	EPressed,
//	EReleased,
//	EHeld
//};
//
//class KeyboardState
//{
//	friend InputManager;
//public:
//	bool GetKeyValue(SDL_Scancode keyCode) const;
//	ButtonState GetKeyState(SDL_Scancode keyCode) const;
//private:
//	const Uint8* currState;
//	Uint8 prevState[SDL_NUM_SCANCODES];
//};
//
//class MouseState
//{
//	friend InputManager;
//public:
//	const glm::vec2& GetPosition() const { return mousePos; }
//	const glm::vec2& GetScrollWheel() const { return scrollWheel; }
//	bool IsRelative() const { return isRelative; }
//
//	bool GetButtonValue(int button) const;
//	ButtonState GetButtonState(int button) const;
//private:
//	glm::vec2 mousePos;
//	glm::vec2 scrollWheel;
//	Uint32 currButtons;
//	Uint32 prevButtons;
//	// 相対であるかどうか
//	bool isRelative;
//};


class InputManager
{
public:
	// OpenGLの初期化の関係でコンストラクタではなくInitialize()を使用する
	// このクラスでは本来コンストラクタを用いることはできるが、他のクラスとフォーマットを揃える
	InputManager(Engine* engine);
	~InputManager();

	bool Initialize(Scene* scene);
	void Shutdown();

	void ProcessInput();
	void ProcessEvent(const SDL_Event& event);

	//void SetRelativeMouseMode(bool value);

private:
	Engine* engine;
	Scene* scene;
	Camera* camera;
	//MouseState mouseState;
	//KeyboardState keyboardState;
};
