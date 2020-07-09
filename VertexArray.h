#pragma once
class VertexArray
{
public:
	VertexArray(const float* verts, unsigned int numVerts,
		const unsigned int* indices, unsigned int numIndices);
	~VertexArray();

	void SetActive();
	unsigned int GetNumIndices() const { return numIndices; }
	unsigned int GetNumVerts() const { return numVerts; }
private:
	// How many vertices in the vertex buffer?
	unsigned int numVerts;
	// How many indices in the index buffer
	unsigned int numIndices;
	// OpenGL ID of the vertex buffer
	unsigned int vertexBuffer;
	// OpenGL ID of the index buffer
	unsigned int indexBuffer;
	// OpenGL ID of the vertex array object
	unsigned int vertexArray;
};

