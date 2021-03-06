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
	static void ProcessNode(Model* model, aiNode* node, const aiScene* scene, std::string directory);
	static Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene, std::string directory);
	static std::vector<Texture> ProcessTextures(const aiMaterial* material, std::string directory);
};
