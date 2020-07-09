#include "Importer.h"
#include "Model.h"
#include <iostream>

namespace Importer
{
bool CheckFileValidity(const std::string& filePath)
{
	struct stat info;
	//file is blocking access or read 
	if (stat(filePath.c_str(), &info) != 0) {
		printf("Cannot access %s\n", filePath.c_str());
		return false;
	}
	//file is accessible
	else if (info.st_mode & S_IFMT) {
		printf("%s is a valid file\n", filePath.c_str());
		return true;
	}
	//File does not exist
	else {
		printf("Error! File: %s does not exist.\n", filePath.c_str());
		return false;
	}
}

std::string GetFileExtension(const std::string& filePath)
{
	size_t indexLocation = filePath.rfind('.', filePath.length());
	if (indexLocation != std::string::npos) {
		return  filePath.substr(indexLocation + 1, filePath.length() - indexLocation);
	}
	return "";
}

Model* ImportModel(std::string path)
{
	Model* model = new Model();

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_OptimizeMeshes | aiProcess_CalcTangentSpace | aiProcess_FlipUVs);

	//useful for texture indexing later
	auto fileExtension = GetFileExtension(path);
	auto directory = path.substr(0, path.find_last_of('/'));
	directory += "/";

	//begin recursive processing of loaded model
	ProcessNode(model, scene->mRootNode, scene);

	return model;
}

void ProcessNode(Model* model, aiNode* node, const aiScene* scene)
{
	//Process all the node meshes
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		model->meshes.push_back(ProcessMesh(mesh, scene));
	}

	//process all the node children recursively
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		ProcessNode(model, node->mChildren[i], scene);
	}
}

Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<unsigned int> textures;

	//Process vertices
	std::cout << "NumVertices: " << mesh->mNumVertices << std::endl;
	for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
		//Process vertex positions, normals, tangents, bitangents, and texture coordinates
		Vertex vertex;
		glm::vec3 vector;

		//Process position
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.position = vector;

		////Process tangent
		//vector.x = mesh->mTangents[i].x;
		//vector.y = mesh->mTangents[i].y;
		//vector.z = mesh->mTangents[i].z;
		//vertex.tangent = vector;

		////Process biTangent
		//vector.x = mesh->mBitangents[i].x;
		//vector.y = mesh->mBitangents[i].y;
		//vector.z = mesh->mBitangents[i].z;
		//vertex.biTangent = vector;

		//Process normals
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.normal = vector;

		//Process texture coords
		//if (mesh->HasTextureCoords(0)) {
		//	glm::vec2 vec;
		//	vec.x = mesh->mTextureCoords[0][i].x;
		//	vec.y = mesh->mTextureCoords[0][i].y;
		//	vertex.texCoords = vec;
		//} else {
		//	vertex.texCoords = glm::vec2(0.0f, 0.0f);
		//}

		vertices.push_back(vertex);
	}

	//Process indices
	std::cout << "NumFaces: " << mesh->mNumFaces << std::endl;
	for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; ++j) {
			indices.push_back(face.mIndices[j]);
		}
	}

	//Process material and texture info
	//aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	//textures = processTextures(material);

	auto newMesh = new Mesh(vertices, indices);
	return newMesh;
}

}