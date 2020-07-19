#pragma once
#include <string>
class Sky
{
public:
	Sky();
	~Sky();

	bool Load(const std::string& filePath);

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

