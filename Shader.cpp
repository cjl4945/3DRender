#include "Shader.h"

Shader::Shader(const char* vertexSource, const char* fragmentSource)
{
	//1. Create and compile the vertex shader
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexSource, nullptr);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");

	//2. Create and compile the fragment shader
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentSource, nullptr);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");

	//3. Link shaders to create the shader program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");

	//4. Delete the shaders as they're linked into our program now
	glDeleteShader(vertex);
	glDeleteShader(fragment);

}

void Shader::use() const
{
	glUseProgram(ID);
}

void Shader::checkCompileErrors(GLuint shader, const std::string& type)
{
	GLint success;
	GLchar infolog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, nullptr, infolog);
			std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: "
				<< type << "\n" << infolog
				<< "\n -----------------------------------------------------------------"
				<< std::endl;
		}
	}
}