#pragma once
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class WindowManager
{
public:
	WindowManager(class Engine* engine);

	bool Initialize(float screenWidth, float screenHeight);
	void Shutdown();
	void UnloadData();
	void SwapWindow();
private:
	SDL_Window* window;
	SDL_GLContext context;
	float screenWidth;
	float screenHeight;

};

