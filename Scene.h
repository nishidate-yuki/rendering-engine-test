#pragma once
#include <vector>

class Model;
class Mesh;
class Shader;

class Scene
{
public:
	Scene(class Engine* engine);
	~Scene();
	bool Initialize(float screenWidth, float screenHeight);
	//void Draw(Shader* shader);
	void Draw();

	bool LoadContent();
	bool LoadShaders();

private:
	class Engine* engine;
	std::vector<Model*> models;
	class Shader* meshShader;
	class Camera* camera;
};

