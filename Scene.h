#pragma once
#include <vector>
#include "Light.h"

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
	bool Initialize(const float screenWidth, const float screenHeight);
	void Draw();
	void Update(const float deltaTime);

	bool LoadContent();
	bool LoadShaders();

	auto GetCamera() const { return camera; }

private:
	Engine* engine;
	std::vector<Model*> models;
	Shader* meshShader;
	Camera* camera;
	DirectionalLight dirLight;
	PointLight pointLight;
};

