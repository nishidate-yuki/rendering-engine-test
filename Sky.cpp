#include "Sky.h"
#include <stb_image.h>
#include <algorithm>
#include <GL/glew.h>
#include "Mesh.h"
#include "Importer.h"

Sky::Sky()
{
}

Sky::~Sky()
{
}

bool Sky::LoadHDRI(const std::string& filePath)
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

Mesh* Sky::CreateCube()
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Vertex vertex;

	vertex.position  = { -1, -1, 1 };
	vertex.normal    = { 0, 0, 1 };
	vertex.texCoords = { 0, 0 };
	vertices.push_back(vertex);

	vertex.position = { -1, 1, 1 };
	vertex.normal = { 1, 0, 0 };
	vertex.texCoords = { 0, 0 };
	vertices.push_back(vertex);


	// Index
	//indices.push_back(face.mIndices[j]);

	return nullptr;
}
