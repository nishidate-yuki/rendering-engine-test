#pragma once
struct Vertex;
class VertexArray
{
public:
	VertexArray(const Vertex* verts, unsigned int numVerts,
		const unsigned int* indices, unsigned int numIndices);
	~VertexArray();

	void Draw();

	void SetActive() const;
	auto GetNumIndices() const { return numIndices; }
	auto GetNumVerts() const { return numVerts; }
private:
	unsigned int numVerts;
	unsigned int numIndices;
	unsigned int vertexBuffer;
	unsigned int indexBuffer;
	unsigned int vertexArray;
};

