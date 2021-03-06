#pragma once
#include <vector>
#include "Light.h"
#include "Sky.h"

class Model;
class Mesh;
class Shader;
class Engine;
class Camera;

enum class Content
{
	Helmet,
	Spheres,
	Sponza
};

class Scene
{
public:
	Scene(Engine* engine);
	~Scene();
	bool Initialize(const float screenWidth, const float screenHeight);
	void Draw();
	void Update(const float deltaTime);

	bool LoadContent(Content cont);
	bool LoadShaders();

	auto GetCamera() const { return camera; }

private:
	Engine* engine;

	// Shader
	Shader* meshShader;

	// Environment
	Sky sky;
	Camera* camera;
	DirectionalLight dirLight;
	PointLight pointLight;

	// Objects
	std::vector<Model*> models;

	unsigned int time = 0;
};

