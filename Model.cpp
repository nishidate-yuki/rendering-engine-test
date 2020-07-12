#include "Model.h"
#include "Shader.h"
#include "Mesh.h"
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform.hpp>

Model::Model()
	: modelMatrix(1.0f)
{
}

void Model::Update(float deltaTime)
{
	glm::mat4 rotateMatrix = glm::rotate(deltaTime, glm::vec3(0, 1, 0));
	modelMatrix *= rotateMatrix;
}

void Model::Draw(Shader* shader)
{
	shader->SetMatrixUniform("uWorldTransform", modelMatrix);
	for (auto mesh : meshes) {
		mesh->Draw(shader);
	}
}

void Model::SetScale(const glm::vec3& scale)
{
	modelMatrix *= glm::scale(scale);
}
