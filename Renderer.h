#pragma once
#include <SDL2/SDL.h>
#include <unordered_map>
#include <glm/glm.hpp>

class Renderer
{
public:
	Renderer(class Engine* engine);
	~Renderer();

	bool Initialize(float screenWidth, float screenHeight);
	void Shutdown();
	void UnloadData();
	
	void Draw();

private:
	bool LoadShaders();

	std::unordered_map<std::string, class Mesh*> meshes;
	class Engine* engine;

	// shader
	class Shader* meshShader;
	class VertexArray* spriteVerts;

	class Scene* scene;

	class Camera* camera;

	// Lighting data
	//glm::vec3 ambientLight;
	//DirectionalLight mDirLight;

	// Window
	SDL_Window* window;

	// OpenGL context
	SDL_GLContext context;

	// Width/height
	float screenWidth;
	float screenHeight;
};

