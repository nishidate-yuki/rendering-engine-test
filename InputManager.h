#pragma once
#include <SDL2/SDL.h>

class Scene;
class Engine;
class Camera;

class InputManager
{
public:
	// OpenGLの初期化の関係でコンストラクタではなくInitialize()を使用する
	// このクラスでは本来コンストラクタを用いることはできるが、WindouwManagerとフォーマットを揃える
	InputManager(Engine* engine);
	~InputManager();

	bool Initialize(Scene* scene);
	void Shutdown();

	void ProcessInput();

private:
	Engine* engine;
	Scene* scene;
	Camera* camera;
};
