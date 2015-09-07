#pragma once
#include "GLEW\glew.h"
#include <map>
#include <string>

using namespace std;

class GLSLShader
{
public:
	GLSLShader(void);
	~GLSLShader(void);

	void LoadFromString(GLenum shaderType, const string& source);
	void LoadFromFile(GLenum shaderType, const string& source);
	void CreateAndLinkProgram();
	void Use();
	void UnUse();
	void AddAttribute(const string& attribute);
	void AddUniform(const string& uniform);
	void DeleteShaderProgram();

	GLuint operator[](const string& attribute);
	GLuint operator()(const string& uniform);

private:
	enum ShaderType
	{
		VERTEX_SHADER,
		FRAGMENT_SHADER,
		GEOMETRY_SHADER
	};

	GLuint _program;
	int _totalShaders;
	GLuint _shaders[3];
	map<string, GLint> _attributeList;
	map<string, GLuint> _uniformLocationList;
};