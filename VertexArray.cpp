#include "VertexArray.h"
#include <GL/glew.h>
#include <iostream>

VertexArray::VertexArray(const float* verts, unsigned int numVerts,
	const unsigned int* indices, unsigned int numIndices)
	: numVerts(numVerts)
	, numIndices(numIndices)
{
	// Create vertex array
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	// Create vertex buffer
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, numVerts * 8 * sizeof(float), verts, GL_STATIC_DRAW);

	// Create index buffer
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	// Specify the vertex attributes
	// (For now, assume one vertex format)
	// Position is 3 floats
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	// Normal is 3 floats
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
		reinterpret_cast<void*>(sizeof(float) * 3));
	// Texture coordinates is 2 floats
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
		reinterpret_cast<void*>(sizeof(float) * 6));
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
	glDeleteVertexArrays(1, &vertexArray);
}

void VertexArray::SetActive()
{
	glBindVertexArray(vertexArray);
}