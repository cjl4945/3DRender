#pragma once

#include <GL/glew.h>
#include "main.h"
#include <iostream>
#include <cstdlib>



class Platform
{
public:
	Platform();
	~Platform();
	void draw() const;

private:
	void generateBuffers();
	void setupBuffers();
	void setVertexAttribs() const;

	GLuint VAO, VBO, EBO;

	static const float vertices[32];

	static const unsigned int indices[6];
};

