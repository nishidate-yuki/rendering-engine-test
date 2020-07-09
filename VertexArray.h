#pragma once
struct Vertex;
class VertexArray
{
public:
	VertexArray(const float* verts, unsigned int numVerts,
		const unsigned int* indices, unsigned int numIndices);
	VertexArray(const Vertex* verts, unsigned int numVerts,
		const unsigned int* indices, unsigned int numIndices);
	~VertexArray();

	void SetActive();
	unsigned int GetNumIndices() const { return numIndices; }
	unsigned int GetNumVerts() const { return numVerts; }
private:
	unsigned int numVerts;
	unsigned int numIndices;
	unsigned int vertexBuffer;
	unsigned int indexBuffer;
	unsigned int vertexArray;
};

