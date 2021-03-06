#pragma once
#include <SDL2/SDL_types.h>
#include "Scene.h"
class WindowManager;
class InputManager;
class Renderer;

class Engine
{
public:
	Engine();
	~Engine();

	bool Initialize();
	void RunLoop();
	void Shutdown();

	void Stop() { isRunning = false; }
	void ResetViewport();

private:
	void ProcessInput();
	void Update();
	void Render();
	void LoadData();

	WindowManager* windowManager;
	InputManager* inputManager;
	Renderer* renderer;
	Scene scene;
	Uint32 ticksCount;
	bool isRunning;
};

