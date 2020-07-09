#pragma once
#include <string>
#include <glm/glm.hpp>
#include <GL/glew.h>

class Shader
{
public:
	Shader();
	~Shader();
	// Load the vertex/fragment shaders with the given names
	bool Load(const std::string& vertName, const std::string& fragName);
	void Unload();
	void SetActive();

	void SetMatrixUniform(const char* name, const glm::mat4& matrix);
	void SetVectorUniform(const char* name, const glm::vec3& vector);
	void SetFloatUniform(const char* name, float value);

private:
	// Tries to compile the specified shader
	bool CompileShader(const std::string& fileName,
		GLenum shaderType,
		GLuint& outShader);

	// Tests whether shader compiled successfully
	bool IsCompiled(GLuint shader);
	// Tests whether vertex/fragment programs link
	bool IsValidProgram();

private:
	// Store the shader object IDs
	GLuint vertexShader;
	GLuint fragShader;
	GLuint shaderProgram;
};

