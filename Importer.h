#pragma once
#include "shader.h"
#include "mesh.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Model;
class Texture;

class Importer
{
public:
	static bool CheckFileValidity(const std::string& filePath);
	static std::string GetFileExtension(const std::string& filePath);

	static Model* ImportModel(std::string path);
	static void ProcessNode(aiNode* node, const aiScene* scene);
	static Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
	static std::vector<unsigned int> ProcessTextures(const aiMaterial* material);

private:
	static Model* model;
	static std::unordered_map<std::string, Texture> textureMap;
	static std::string directory, fileExtension;
};
