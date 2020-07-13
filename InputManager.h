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
	// OpenGL�̏������̊֌W�ŃR���X�g���N�^�ł͂Ȃ�Initialize()���g�p����
	// ���̃N���X�ł͖{���R���X�g���N�^��p���邱�Ƃ͂ł��邪�A���̃N���X�ƃt�H�[�}�b�g�𑵂���
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
