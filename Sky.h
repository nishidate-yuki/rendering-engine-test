#pragma once
#include <string>
#include <glm/glm.hpp>

class Shader;
class VertexArray;

class Sky
{
public:
	Sky();
	~Sky();

	bool Initialize(const std::string& filePath);
	bool LoadHDRI(const std::string& filePath);
	void CreateCube();

	void SetActive() const;
	//void Draw(Shader* shader);
	void Draw(glm::mat4 view, glm::mat4 projection);

	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
	//int GetTextureID() const { return textureID; }

	// TODO: リファクタ
	void CreateCubemap();
	void RenderCube();
	unsigned int captureFBO;
	unsigned int captureRBO;
	unsigned int envCubemap;
	unsigned int cubeVAO = 0;
	unsigned int cubeVBO = 0;
	Shader* skyShader;

private:
	VertexArray* vertexArray;
	unsigned int hdrTexture;
	int width;
	int height;
	int channels;
	Shader* toCubemapShader;
};

