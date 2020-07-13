#pragma once
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class Scene;
class Engine;
class Camera;
class InputManager;

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

private:
	Engine* engine;
	Scene* scene;
	Camera* camera;
};
