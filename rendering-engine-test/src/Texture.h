#pragma once
#include <string>

enum class TextureType
{
	Diffuse,
	Emissive,
	Normal,
	AmbientOcclusion,
	MetalRoughness
};

class Texture
{
public:
	Texture();
	~Texture();

	bool Load(const std::string& filePath);
	void Unload();

	void SetActive() const;

	void SetType(TextureType type) { this->type = type; }
	auto GetType() { return type; }
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
	int GetTextureID() const { return textureID; }
private:
	unsigned int textureID;
	TextureType type;
	int width;
	int height;
	int channels;
};
