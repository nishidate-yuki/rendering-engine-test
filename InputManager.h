#pragma once
#include <SDL2/SDL.h>

class Scene;
class Engine;
class Camera;

class InputManager
{
public:
	// OpenGL�̏������̊֌W�ŃR���X�g���N�^�ł͂Ȃ�Initialize()���g�p����
	// ���̃N���X�ł͖{���R���X�g���N�^��p���邱�Ƃ͂ł��邪�AWindouwManager�ƃt�H�[�}�b�g�𑵂���
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
