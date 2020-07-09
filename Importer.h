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

namespace Importer
{
	bool CheckFileValidity(const std::string& filePath);
	std::string GetFileExtension(const std::string& filePath);

	Model* ImportModel(std::string path);
	void ProcessNode(Model* model, aiNode* node, const aiScene* scene);
	Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);

};

