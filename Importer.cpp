#include "Importer.h"
#include "Model.h"
#include <iostream>

// staticƒƒ“ƒo•Ï”‚ÍŽÀ‘Ì‚ðì‚é•K—v‚ª‚ ‚é
Model* Importer::model;
std::string Importer::directory, Importer::fileExtension;

bool Importer::CheckFileValidity(const std::string& filePath)
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
	//Model* model = new Model();
	model = new Model();

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, 
		aiProcess_Triangulate | aiProcess_OptimizeMeshes 
		| aiProcess_CalcTangentSpace | aiProcess_FlipUVs);

	//useful for texture indexing later
	fileExtension = GetFileExtension(path);
	directory = path.substr(0, path.find_last_of('/'));
	directory += "/";

	//begin recursive processing of loaded model
	ProcessNode(scene->mRootNode, scene);

	return model;
}

void Importer::ProcessNode(aiNode* node, const aiScene* scene)
{
	//Process all the node meshes
	std::cout << "NumMeshes: " << node->mNumMeshes << std::endl;
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		model->meshes.push_back(ProcessMesh(mesh, scene));
	}

	//process all the node children recursively
	std::cout << "NumChildren: " << node->mNumChildren << std::endl;
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh* Importer::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<unsigned int> textures;

	//Process vertices
	std::cout << "NumVertices: " << mesh->mNumVertices << std::endl;
	for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
		//Process vertex positions, normals, tangents, bitangents, and texture coordinates
		Vertex vertex;

		//Process position
		vertex.position.x = mesh->mVertices[i].x;
		vertex.position.y = mesh->mVertices[i].y;
		vertex.position.z = mesh->mVertices[i].z;

		////Process tangent
		vertex.tangent.x = mesh->mTangents[i].x;
		vertex.tangent.y = mesh->mTangents[i].y;
		vertex.tangent.z = mesh->mTangents[i].z;

		////Process biTangent
		vertex.biTangent.x = mesh->mBitangents[i].x;
		vertex.biTangent.y = mesh->mBitangents[i].y;
		vertex.biTangent.z = mesh->mBitangents[i].z;

		//Process normals
		vertex.normal.x = mesh->mNormals[i].x;
		vertex.normal.y = mesh->mNormals[i].y;
		vertex.normal.z = mesh->mNormals[i].z;

		//Process texture coords
		if (mesh->HasTextureCoords(0)) {
			vertex.texCoords.x = mesh->mTextureCoords[0][i].x;
			vertex.texCoords.y = mesh->mTextureCoords[0][i].y;
		} else {
			vertex.texCoords = glm::vec2(0.0f, 0.0f);
		}

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
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	std::cout <<"NumProperties: " << material->mNumProperties << std::endl;
	//textures = ProcessTextures(material);

	return new Mesh(vertices, indices);
}
//
//std::vector<unsigned int> Importer::ProcessTextures(const aiMaterial* material)
//{
//	std::vector<unsigned int> textures;
//
//	//Finding current texture directory
//	aiString texturePath;
//	aiTextureType type;
//	std::string fullTexturePath;
//
//	//Checking all texture stacks for each texture type
//	//Checkout assimp docs on texture types
//	for (int tex = aiTextureType_NONE; tex <= aiTextureType_UNKNOWN; tex++) {
//		type = static_cast<aiTextureType>(tex); //making the int value into the enum value
//		fullTexturePath = directory;
//
//		//If there are any textures of the given type in the material
//		if (material->GetTextureCount(type) > 0) {
//			//We only care about the first texture assigned we don't expect multiple to be assigned
//			material->GetTexture(type, 0, &texturePath);
//			fullTexturePath = fullTexturePath.append(texturePath.C_Str());
//
//			//If this texture has not been added to the atlas yet we load it
//			if (textureMap.count(fullTexturePath) == 0) {
//				Texture texture;
//				bool srgb = false;
//				texture.loadTexture(fullTexturePath, srgb);
//				textureMap.insert({ fullTexturePath, texture });
//			}
//
//			//We add it to the texture index array of loaded texture for a given mesh
//			textures.push_back(textureMap.at(fullTexturePath).textureID);
//		} else {
//			//For now we always assume that these textures will exist in the current
//			//material. If they do not, we assign 0 to their value.
//			//This will be fixed when the new material model is implemented.
//			switch (type) {
//				case aiTextureType_LIGHTMAP:
//				case aiTextureType_EMISSIVE:
//				case aiTextureType_NORMALS:
//				case aiTextureType_UNKNOWN:
//					textures.push_back(0);
//					break;
//			}
//		}
//	}
//	return textures;
//}
