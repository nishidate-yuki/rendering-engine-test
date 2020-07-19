#include "Sky.h"
#include <stb_image.h>
#include <algorithm>
#include <GL/glew.h>

Sky::Sky()
{
}

Sky::~Sky()
{
}

bool Sky::Load(const std::string& filePath)
{
	std::string path = filePath;
	std::replace(path.begin(), path.end(), '\\', '/');

	// Load
	float* data = stbi_loadf(path.c_str(), &width, &height, &channels, 0);
	if (!data) {
		printf("Texture failed to load at path: %s \n", path.c_str());
		return false;
	}

	// Generate texture (Get texture ID on GPU)
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, data);

	// Set parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);

	return true;
}

void Sky::SetActive() const
{
}
