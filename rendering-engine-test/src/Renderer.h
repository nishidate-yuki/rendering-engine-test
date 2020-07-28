#pragma once
#include <SDL2/SDL.h>
#include <unordered_map>
#include <glm/glm.hpp>

class Engine;
class Scene;
class Camera;
class WindowManager;

class Renderer
{
public:
	Renderer(Engine* engine);
	~Renderer();

	bool Initialize(WindowManager* windowManager, Scene* scene);
	void Shutdown();
	void UnloadData();
	
	void Draw();

private:
	Engine* engine;
	Scene* scene;
	Camera* camera;
	WindowManager* windowManager;

	float screenWidth;
	float screenHeight;

};

