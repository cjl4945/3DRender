#pragma once
#include <GL/glew.h>
#include "main.h"
#include <iostream>
#include <cstdlib>

class Cube
{
private:
	void generateBuffers();
	void setupBuffers();
	void setVertexAttribs() const;
	GLuint VAO, VBO, EBO;

	//Vertex data for a cube (8 corners)
	static const float vertices[24];

	// Index data for the 12 triangles (36 indices) taht compose a cube
	static const unsigned int indices[36];

public:
	Cube(); 
	~Cube();
	
	void draw() const;
};





