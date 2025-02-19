#include "geometry.h"

using namespace std;

float vertices[24] =
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

unsigned int indices[36] =
{
	0,1,2,	2,3,0, //Back face 
	4,5,6,	6, 7, 4, //Front face
	0,4,7,	7,3,0, //Left face
	1,5,6,	6,2,1, // Right face
	3,2,6,	6,7,3,	//Top Face
	0,1,5,	5,4,0 //Bottom face
};

unsigned int VAO, VBO, EBO;

//Generate the VAO, VBO, and EBO identifiers 
void generateIdentifiers()
{
	glGenVertexArrays(1, &VAO);
	if (!VAO)
	{
		cerr << "Failed to generate vertex array object: " << glGetError() << endl;
		exit(-1);
	}
	glGenBuffers(1, &VBO);
	if (!VBO)
	{
		cerr << "Failed to generate vertex buffer object: " << glGetError() << endl;
		exit(-1);
	}
	glGenBuffers(1, &EBO);
	if (!EBO)
	{
		cerr << "Failed to generate element buffer object: " << glGetError() << endl;
		exit(-1);
	}
}

//Bind and fill the VAO with vertex  data
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
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