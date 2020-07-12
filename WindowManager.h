#pragma once
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class Engine;

class WindowManager
{
public:
	// OpenGL�̏������̊֌W�ŃR���X�g���N�^�ł͂Ȃ�Initialize()���g�p����
	WindowManager(Engine* engine);

	bool Initialize(float screenWidth, float screenHeight);
	void Shutdown();
	void UnloadData();
	void SwapWindow();
	float GetScreenWidth() { return screenWidth; }
	float GetScreenHeight() { return screenHeight; }
private:
	SDL_Window* window;
	SDL_GLContext context;
	float screenWidth;
	float screenHeight;
};

