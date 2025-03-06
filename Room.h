#pragma once

#include <GL/glew.h>
#include "main.h"
#include <iostream>
#include <cstdlib>



class Room
{
public:
	Room();
	~Room();
	void draw() const;

private:
	void generateBuffers();
	void setupBuffers();
	void setVertexAttribs() const;

	GLuint VAO, VBO, EBO;

	static const float vertices[192];

	static const unsigned int indices[36];
};

