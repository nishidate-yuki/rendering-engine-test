#pragma once
#include <string>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Light.h"

class Shader
{
public:
	Shader();
	~Shader();
	// Load the vertex/fragment shaders with the given names
	bool Load(const std::string& vertName, const std::string& fragName);
	void Unload();
	void SetActive() const;

	void SetMatrix(const char* name, const glm::mat4& matrix);
	void SetVector(const char* name, const glm::vec3& vector);
	void SetFloat(const char* name, float value);
	void SetInt(const char* name, int value);
	void SetDirectionalLight(const std::string name, const DirectionalLight dirLight);

private:
	bool CompileShader(const std::string& fileName,
		GLenum shaderType, GLuint& outShader);

	bool IsCompiled(GLuint shader);
	bool IsValidProgram();

private:
	// Shader object IDs
	GLuint vertexShader;
	GLuint fragShader;
	GLuint shaderProgram;
};

