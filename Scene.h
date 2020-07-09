#pragma once
#include <vector>

class Model;
class Mesh;
class Shader;

class Scene
{
public:
	Scene();
	void Draw(Shader* shader);

	void LoadContent();

private:
	//std::vector<Model*> models;
	std::vector<Mesh*> meshes;
};

