#pragma once
#include <string>
class Mesh;
class Sky
{
public:
	Sky();
	~Sky();

	bool LoadHDRI(const std::string& filePath);

	void SetActive() const;

	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
	int GetTextureID() const { return textureID; }

	Mesh* CreateCube();

private:
	Mesh* cube;
	unsigned int textureID;
	int width;
	int height;
	int channels;
};

