#include "Platform.h"

const float Platform::vertices[32] 
{
	//positions				//normals (pointing up) (nx, ny**, nz)
	-2.0f, 0.0f, -2.0f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
	2.0f, 0.0f, -2.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
	2.0f, 0.0f, 2.0f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
	-2.0f, 0.0f, 2.0f,		0.0f, 1.0f, 0.0f,	0.0, 1.0f

};

const unsigned int Platform::indices[6]
{
	0, 1, 2,
	2, 3, 0
};


Platform::Platform() : VAO(0), VBO(0), EBO(0)
{
	generateBuffers();
	setupBuffers();
}
Platform::~Platform()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
}

void Platform::generateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

void Platform::setupBuffers()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cerr << "Error while binding/filling VBO: " << error << std::endl;
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cerr << "Error while binding/filling EBO: " << error << std::endl;
	}


	setVertexAttribs();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}


void Platform::setVertexAttribs() const
{
	////Assummin the shader uses location 0 for the position attribute.
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	// Attribute 0: position (first 3 floats)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Attribute 1: normal (next 3 floats)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//Attribute 2: texture coordinates (last 2 floats)
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}
void Platform::draw() const
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


