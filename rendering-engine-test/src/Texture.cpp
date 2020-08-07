#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <algorithm>
#include <GL/glew.h>

Texture::Texture()
	: type(TextureType::Diffuse)
{
}

Texture::~Texture()
{
}

bool Texture::Load(const std::string& filePath)
{
	std::string path = filePath;
	std::replace(path.begin(), path.end(), '\\', '/');

	// Load
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
	if (!data) {
		printf("Texture failed to load at path: %s \n", path.c_str());
		return false;
	}

	// Set format
	// TODO: support SRGB
	GLenum format = GL_RGB;
	if (channels == 4) {
		format = GL_RGBA;
	}

	// Generate texture (Get texture ID on GPU)
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	//MipMapped and repeating
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);

	return true;
}

void Texture::Unload()
{
	glDeleteTextures(1, &textureID);
}

void Texture::SetActive() const
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}
