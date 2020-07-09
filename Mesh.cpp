#include "Mesh.h"
#include "VertexArray.h"
#include "Shader.h"

Mesh::Mesh()
{
	worldTransform = glm::mat4(1.0f);
}

void Mesh::Draw(Shader* shader)
{
	shader->SetMatrixUniform("uWorldTransform", worldTransform);
	vertexArray->SetActive();
	glDrawElements(GL_TRIANGLES,
		vertexArray->GetNumIndices(), 
		GL_UNSIGNED_INT, nullptr);
}

void Mesh::CreateQuads()
{
	// pos, nor, tex
	float vertices[] = {
		-0.5f, 0.5f, 0.f, 0.f, 0.f, 1.0f, 0.f, 0.f, // top left
		0.5f, 0.5f, 0.f, 0.f, 0.f, 1.0f, 1.f, 0.f, // top right
		0.5f,-0.5f, 0.f, 0.f, 0.f, 1.0f, 1.f, 1.f, // bottom right
		-0.5f,-0.5f, 0.f, 0.f, 0.f, 1.0f, 0.f, 1.f  // bottom left
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	vertexArray = new VertexArray(vertices, 4, indices, 6);
}
