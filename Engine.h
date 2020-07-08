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

private:
	void ProcessInput();
	void Update();
	void Render();
	void LoadData();

	class Renderer* renderer;
	Uint32 ticksCount;
	bool isRunning;
};

