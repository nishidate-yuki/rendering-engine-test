#pragma once
#include <SDL2/SDL_types.h>

class Engine
{
public:
	Engine();
	~Engine();

	bool Initialize();
	void RunLoop();
	void Shutdown();

	void Stop() { isRunning = false; }

private:
	void ProcessInput();
	void Update();
	void Render();
	void LoadData();

	class WindowManager* windowManager;
	class InputManager* inputManager;
	class Renderer* renderer;
	class Scene* scene;
	Uint32 ticksCount;
	bool isRunning;
};

