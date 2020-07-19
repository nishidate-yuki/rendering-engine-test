#pragma once
#include <string>
class Shader;
class VertexArray;
class Sky
{
public:
	Sky();
	~Sky();

	void Initialize(const std::string& filePath);
	bool LoadHDRI(const std::string& filePath);
	void CreateBox();

	void SetActive() const;
	void Draw(Shader* shader);

	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
	int GetTextureID() const { return textureID; }
private:
	VertexArray* vertexArray;
	unsigned int textureID;
	int width;
	int height;
	int channels;
};

