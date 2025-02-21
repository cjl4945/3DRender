#include "Cube.h"


const float Cube::vertices[144] =
{
	//-0.5f, -0.5f, -0.5f, //Vertex 0:  bottom left back
	//0.5f, -0.5f, -0.5f, //Vertex 1: bottom right back 
	//0.5f, 0.5f, -0.5f, //Vertex 2: bottom right front
	//-0.5f, 0.5f, -0.5f, //Vertex 3 bottom left front

	//-0.5f, -0.5f, 0.5f, //Vertex 4 top left back
	//0.5f, -0.5f, 0.5f, //Vertex 5 top right back
	//0.5f, 0.5f, 0.5f, //Vertex 6 top left front
	//-0.5f, 0.5f, 0.5f, //Vertex 7 top right front

	 // Front face (normal: 0, 0, 1)
	-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  // Vertex 0
	 0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  // Vertex 1
	 0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  // Vertex 2
	-0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  // Vertex 3

	// Back face (normal: 0, 0, -1)
	 0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  // Vertex 4
	-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  // Vertex 5
	-0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  // Vertex 6
	 0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  // Vertex 7

	 // Left face (normal: -1, 0, 0)
	 -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  // Vertex 8
	 -0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,  // Vertex 9
	 -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,  // Vertex 10
	 -0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  // Vertex 11

	 // Right face (normal: 1, 0, 0)
	  0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,  // Vertex 12
	  0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,  // Vertex 13
	  0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,  // Vertex 14
	  0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,  // Vertex 15

	  // Top face (normal: 0, 1, 0)
	  -0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,  // Vertex 16
	   0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,  // Vertex 17
	   0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,  // Vertex 18
	  -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,  // Vertex 19

	  // Bottom face (normal: 0, -1, 0)
	  -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,  // Vertex 20
	   0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,  // Vertex 21
	   0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,  // Vertex 22
	  -0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f   // Vertex 23

};

const unsigned int Cube::indices[36] =
{
	//0,1,5,	5,4,0, //Back face 
	//3,2,3,	6, 7, 3, //Front face
	//0,3,7,	7,4,0, //Left face
	//1,2,6,	6,5,1, // Right face
	//4,5,6,	6,7,4,	//Top Face
	//0,1,2,	2,3,0 //Bottom face

	// Front face
	0, 1, 2,  2, 3, 0,
	// Back face
	4, 5, 6,  6, 7, 4,
	// Left face
	8, 9, 10,  10, 11, 8,
	// Right face
	12, 13, 14,  14, 15, 12,
	// Top face
	16, 17, 18,  18, 19, 16,
	// Bottom face
	20, 21, 22,  22, 23, 20
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
	glGenBuffers(1, &EBO);
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
	////Assummin the shader uses location 0 for the position attribute.
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	// Attribute 0: position (first 3 floats)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Attribute 1: normal (next 3 floats)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void Cube::draw() const {
	//Bind the VAO and issue the draw call.
	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}