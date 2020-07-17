#pragma once
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class Engine;

class WindowManager
{
public:
	// OpenGLの初期化の関係でコンストラクタではなくInitialize()を使用する
	WindowManager(Engine* engine);

	bool Initialize(float screenWidth, float screenHeight);
	void Shutdown();
	void UnloadData();
	void SwapWindow();
	auto GetScreenWidth() const { return screenWidth; }
	auto GetScreenHeight() const { return screenHeight; }
private:
	SDL_Window* window;
	SDL_GLContext context;
	float screenWidth;
	float screenHeight;
};

