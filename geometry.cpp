#include "geometry.h"

//Generate the VAO, VBO, and EBO identifiers 
void generateIdentifiers()
{
	glGenVertexArrays(1, &VAO);
	if (!VAO)
	{
		cerr << "Failed to generate vertex array object: " << glGetError << endl;
		exit(-1);
	}
	glGenBuffers(1, &VBO);
	if (!VBO)
	{
		cerr << "Failed to generate vertex buffer object: " << glGetError << endl;
		exit(-1);
	}
	glGenBuffers(1, &EBO);
	if (!EBO)
	{
		cerr << "Failed to element buffer object: " << glGetError << endl;
		exit(-1);
	}
}

//Bind and fill the VBO with vertex  data
void bindVAO() 
{
	glBindVertexArray(VAO);
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) 
	{
		cerr << "Failed VAO binding: " << error << endl;
	}
}

//bind and fill with the VBO with vertex data
void bindFillVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		cerr << "Failed VBO binding: " << error << endl;
	}
}
void bindFillEBO() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		cerr << "Failed EBO binding: " << error << endl;
	}
}

void setVertexAttributesPtrs()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void unbindVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}