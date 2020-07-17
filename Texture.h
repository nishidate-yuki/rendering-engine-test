#pragma once
#include <string>
class Texture
{
public:
	Texture();
	~Texture();

	bool Load(const std::string& filePath);
	void Unload();

	void SetActive() const;

	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
	int GetTextureID() const { return textureID; }
private:
	unsigned int textureID;
	int width;
	int height;
	int channels;
};
