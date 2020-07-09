#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <unordered_map>

class Mesh;
class Shader;

class Model
{
public:
	Model();

	//Model(const std::string meshPath, const TransformParameters initParameters, bool IBL) : IBL(IBL)
	//{
	//	loadModel(meshPath);
	//	modelMatrix = glm::mat4(1.0);
	//	modelMatrix = glm::translate(modelMatrix, initParameters.translation);
	//	modelMatrix = glm::rotate(modelMatrix, initParameters.angle, initParameters.rotationAxis);
	//	modelMatrix = glm::scale(modelMatrix, initParameters.scaling);
	//}

	//Base interface
	void LoadQuad();
	//void loadModel(std::string path);
	//void update(const unsigned int deltaT);
	void Draw(Shader* shader);

	//Model processing/loading functions
	//void processNode(aiNode* node, const aiScene* scene);
	//Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	//std::vector<unsigned int> processTextures(const aiMaterial* material);

	//Object to world space matrix
	glm::mat4 modelMatrix;
	std::vector<Mesh*> meshes; //Does it need to be a vector after initialization?

	//To avoid textures being loaded from disk more than once they are indexed into a dictionary
	//std::unordered_map<std::string, Texture> textureAtlas;
	//std::string directory, fileExtension;
};
