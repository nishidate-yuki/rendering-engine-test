#include "Mesh.h"
#include "VertexArray.h"
#include "Shader.h"
#include <vector>

Mesh::Mesh()
{
}

Mesh::Mesh(std::vector<Vertex>& vertices,
		   std::vector<unsigned int>& indices)
{
	vertexArray = new VertexArray(&vertices[0], vertices.size(), &indices[0], indices.size());
}

void Mesh::Draw(Shader* shader)
{
	vertexArray->SetActive();
	glDrawElements(GL_TRIANGLES,
		vertexArray->GetNumIndices(), 
		GL_UNSIGNED_INT, nullptr);
}
