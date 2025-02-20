#include "Cube.h"


const float Cube::vertices[24] =
{
	-0.5f, 0.5f, -0.5f, //Vertex 0
	0.5f, -0.5f, -0.5f, //Vertex 1
	0.5f, 0.5f, -0.5f, //Vertex 2
	-0.5f, 0.5f, -0.5f, //Vertex 3
	-0.5f, -0.5f, 0.5f, //Vertex 4
	0.5f, -0.5f, 0.5f, //Vertex 5
	0.5f, 0.5f, 0.5f, //Vertex 6
	-0.5f, 0.5f, 0.5f, //Vertex 7
};

const unsigned int Cube::indices[36] =
{
	0,1,2,	2,3,0, //Back face 
	4,5,6,	6, 7, 4, //Front face
	0,4,7,	7,3,0, //Left face
	1,5,6,	6,2,1, // Right face
	3,2,6,	6,7,3,	//Top Face
	0,1,5,	5,4,0 //Bottom face
};

Cube::Cube() : VAO(0), VBO(0), EBO(0)
{
	generateBuffers();
	setupBuffers();
}

Cube::~Cube()
{
	//Clean up OpenGL resources.
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
}

void Cube::generateBuffers()
{
	glGenVertexArrays(1, &VAO);
	if (!VAO)
	{
		std::cerr << "Failed to generate vertex array object: " << glGetError() << std::endl; exit(EXIT_FAILURE);
	}
	glGenBuffers(1, &VBO);
	if (!VBO)
	{
		std::cerr << "Failed to generate vertex buffer object: " << glGetError() << std::endl; exit(EXIT_FAILURE);
	}
	glGenVertexArrays(1, &EBO);
	if (!EBO)
	{
		std::cerr << "Failed to generate element buffer object: " << glGetError() << std::endl; exit(EXIT_FAILURE);
	}
}

void Cube::setupBuffers()
{
	//Bind VAO so that all subsequent configuration is stored in it.
	glBindVertexArray(VAO);
	// Bind and set data for the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cerr << "Error while binding/filling VBO: " << error << std::endl;
	}

	//Bind and set data for the EBO.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cerr << "Error while binding/filling EBO: " << error << std::endl;
	}

	//Set up the vertex attribute pointers.
	setVertexAttribs();

	//Unbind the VBO (the VAO will keep the configuration).
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

}
void Cube::setVertexAttribs() const {
	//Assummin the shader uses location 0 for the position attribute.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Cube::draw() const {
	//Bind the VAO and issue the draw call.
	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}