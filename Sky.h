#pragma once
#include <string>
#include <glm/glm.hpp>

class Shader;
class Engine;

class Sky
{
public:
	Sky();
	~Sky();

	bool Initialize(const std::string& filePath, Engine* engine=nullptr);
	void Draw(glm::mat4 view, glm::mat4 projection);

private:
	void CreateCube();
	void RenderCube();
	void CreateCubemap();
	bool LoadHDRI(const std::string& filePath);
	unsigned int captureFBO;
	unsigned int captureRBO;
	unsigned int envCubemap;
	unsigned int cubeVAO;
	unsigned int cubeVBO;

	unsigned int hdrTexture;
	int width;
	int height;
	int channels;
	Shader* skyShader;
	Shader* toCubemapShader;
};

