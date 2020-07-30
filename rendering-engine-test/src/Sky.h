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
	auto GetIrradianceMap() { return irradianceMap; }
	auto GetEnvCubemap() { return envCubemap; }
	auto GetPrefilterMap() { return prefilterMap; }
	auto GetBrdfLUT() { return brdfLUT; }

private:
	void CreateCube();
	void RenderCube();
	void RenderQuad();

	void BuildCubemapFrom2DTexture();
	void ConvoluteCubemap();
	void PreFilterEnvMap();
	void CalcBRDFtexture();

	bool LoadHDRI(const std::string& filePath);
	unsigned int captureFBO;
	unsigned int captureRBO;
	unsigned int cubeVAO;
	unsigned int cubeVBO;
	unsigned int quadVAO;
	unsigned int quadVBO;

	unsigned int hdrTexture;
	unsigned int envCubemap;
	unsigned int irradianceMap;
	unsigned int prefilterMap;
	unsigned int brdfLUT;
	int width;
	int height;
	int channels;
	Shader* skyShader;
	Shader* toCubemapShader;
	Shader* irradianceShader;
	Shader* prefilterShader;
	Shader* brdfShader;

	glm::mat4 captureProjection;
	glm::mat4 captureViews[6];
};

