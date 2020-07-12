#include "Importer.h"
#include "Model.h"
#include "Texture.h"
#include <iostream>

// staticメンバ変数は実体を作る必要がある
// Importer:: をつけるのを忘れないようにする
Model* Importer::model;
std::string Importer::directory, Importer::fileExtension;
std::unordered_map<std::string, Texture> Importer::textureMap;

bool Importer::CheckFileValidity(const std::string& filePath)
{
	struct stat info;
	// file is blocking access or read 
	if (stat(filePath.c_str(), &info) != 0) {
		printf("Cannot access %s\n", filePath.c_str());
		return false;
	}
	// file is accessible
	else if (info.st_mode & S_IFMT) {
		printf("%s is a valid file\n", filePath.c_str());
		return true;
	}
	// File does not exist
	else {
		printf("Error! File: %s does not exist.\n", filePath.c_str());
		return false;
	}
}

std::string Importer::GetFileExtension(const std::string& filePath)
{
	size_t indexLocation = filePath.rfind('.', filePath.length());
	if (indexLocation != std::string::npos) {
		return  filePath.substr(indexLocation + 1, filePath.length() - indexLocation);
	}
	return "";
}

Model* Importer::ImportModel(std::string path)
{
	model = new Model();

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, 
		aiProcess_Triangulate | aiProcess_OptimizeMeshes 
		| aiProcess_CalcTangentSpace | aiProcess_FlipUVs);

	// useful for texture indexing later
	fileExtension = GetFileExtension(path);
	directory = path.substr(0, path.find_last_of('/'));
	directory += "/";

	// ルートからノードを再帰処理
	ProcessNode(scene->mRootNode, scene);

	return model;
}

void Importer::ProcessNode(aiNode* node, const aiScene* scene)
{
	// Meshes
	std::cout << "NumMeshes: " << node->mNumMeshes << std::endl;
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		model->meshes.push_back(ProcessMesh(mesh, scene));
	}

	// Children を再帰処理
	std::cout << "NumChildren: " << node->mNumChildren << std::endl;
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh* Importer::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	//Process vertices
	std::cout << "NumVertices: " << mesh->mNumVertices << std::endl;
	for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
		Vertex vertex;

		// Position
		vertex.position.x = mesh->mVertices[i].x;
		vertex.position.y = mesh->mVertices[i].y;
		vertex.position.z = mesh->mVertices[i].z;

		// Tangent
		vertex.tangent.x = mesh->mTangents[i].x;
		vertex.tangent.y = mesh->mTangents[i].y;
		vertex.tangent.z = mesh->mTangents[i].z;

		// BiTangent
		vertex.biTangent.x = mesh->mBitangents[i].x;
		vertex.biTangent.y = mesh->mBitangents[i].y;
		vertex.biTangent.z = mesh->mBitangents[i].z;

		// Normal
		vertex.normal.x = mesh->mNormals[i].x;
		vertex.normal.y = mesh->mNormals[i].y;
		vertex.normal.z = mesh->mNormals[i].z;

		// Texture coordinates
		if (mesh->HasTextureCoords(0)) {
			vertex.texCoords.x = mesh->mTextureCoords[0][i].x;
			vertex.texCoords.y = mesh->mTextureCoords[0][i].y;
		} else {
			vertex.texCoords = glm::vec2(0.0f, 0.0f);
		}

		vertices.push_back(vertex);
	}

	// Index
	std::cout << "NumFaces: " << mesh->mNumFaces << std::endl;
	for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; ++j) {
			indices.push_back(face.mIndices[j]);
		}
	}

	// Material / Texture
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	textures = ProcessTextures(material);
	std::cout << "NumTextures: " << textures.size() << std::endl;

	return new Mesh(vertices, indices, textures);
}

std::vector<Texture> Importer::ProcessTextures(const aiMaterial* material)
{
	std::vector<Texture> textures;

	aiString texturePath;
	aiTextureType type;
	std::string fullTexturePath;

	// -------------- aiTextureType --------------
	// aiTextureType_NONE				= 0
	// aiTextureType_DIFFUSE			= 1
	// aiTextureType_SPECULAR			= 2
	// aiTextureType_AMBIENT			= 3
	// aiTextureType_EMISSIVE			= 4
	// aiTextureType_HEIGHT				= 5
    // aiTextureType_NORMALS			= 6
	// aiTextureType_SHININESS			= 7
	// aiTextureType_OPACITY			= 8
	// aiTextureType_DISPLACEMENT		= 9
	// aiTextureType_LIGHTMAP			= 10
	// aiTextureType_REFLECTION			= 11
	// aiTextureType_BASE_COLOR			= 12
	// aiTextureType_NORMAL_CAMERA		= 13
	// aiTextureType_EMISSION_COLOR		= 14
	// aiTextureType_METALNESS			= 15
	// aiTextureType_DIFFUSE_ROUGHNESS  = 16
	// aiTextureType_AMBIENT_OCCLUSION  = 17
	// aiTextureType_UNKNOWN			= 18
	// -------------------------------------------

	// 各テクスチャタイプごとにスタックをチェックする
	for (int tex = aiTextureType_NONE; tex <= aiTextureType_UNKNOWN; tex++) {
		type = static_cast<aiTextureType>(tex); //　int -> enum
		fullTexturePath = directory;

		// マテリアルに指定されたタイプのテクスチャがある場合
		if (material->GetTextureCount(type) > 0) {
			// 最初に割り当てられたテクスチャのみに対応している
			// つまり、各テクスチャタイプごとに1枚だけ読み込む
			material->GetTexture(type, 0, &texturePath);
			fullTexturePath = fullTexturePath.append(texturePath.C_Str());

			// テクスチャマップにまだ無い場合はロードする
			if (textureMap.count(fullTexturePath) == 0) {
				Texture texture;
				texture.Load(fullTexturePath);
				textureMap.insert({ fullTexturePath, texture });
				std::cout << "FullTexturePath:" << fullTexturePath << std::endl;
			}

			// テクスチャ配列に追加
			textures.push_back(textureMap.at(fullTexturePath));
		}
	}
	return textures;
}
