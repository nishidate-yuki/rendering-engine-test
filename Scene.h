#pragma once
#include <vector>

class Model;
class Mesh;
class Shader;
class Engine;
class Camera;

class Scene
{
public:
	Scene(Engine* engine);
	~Scene();
	bool Initialize(float screenWidth, float screenHeight);
	void Draw();
	void Update(float deltaTime);

	bool LoadContent();
	bool LoadShaders();

	auto GetCamera() { return camera; }

private:
	Engine* engine;
	std::vector<Model*> models;
	Shader* meshShader;
	Shader* normalShader;
	Camera* camera;
};

