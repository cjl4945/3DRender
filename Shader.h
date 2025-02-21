#pragma once

#include "GL/glew.h"
#include <string>
#include <iostream>

class Shader
{
public:
	GLuint ID;

	Shader(const char* vertexSource, const char* fragmentSource);

	void use() const;


private:
	void checkCompileErrors(GLuint shader, const std::string& type);
};