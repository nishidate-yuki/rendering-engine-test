#include "Model.h"
#include "Shader.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>

Model::Model()
	: modelMatrix(1.0f)
{
}

Model::~Model()
{
	while (!meshes.empty()) {
		delete meshes.back();
	}
}

void Model::Update(const float deltaTime)
{
	//glm::mat4 rotateMatrix = glm::rotate(deltaTime, glm::vec3(0, 1, 0));
	//modelMatrix *= rotateMatrix;
}

void Model::Draw(Shader* shader)
{
	shader->SetMatrix("model", modelMatrix);
	for (auto mesh : meshes) {
		mesh->Draw(shader);
	}
}

void Model::SetScale(const glm::vec3& scale)
{
	modelMatrix *= glm::scale(scale);
}