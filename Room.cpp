#include "Room.h"

//The room will span from -5 to 5 in X and Z, floor sy y=0 and ceiling at y=5
//vertices for each face, normal vectors are pointing inward to light the interior
//Each vertex: [x, y, z, nx, ny, nz, u, v]


//need to change the room to dynamically add walls we
const float Room::vertices[192]
{
	//Floor (y=0) - normals point up
	-5.0f, 0.0f, -5.0f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f, //0
	5.0f, 0.0f, -5.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f, //1
	5.0f, 0.0f, 5.0f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f, //2
	-5.0f, 0.0f, 5.0f,		0.0f, 1.0f, 0.0f,	0.0, 1.0f, //3

	// Ceiling (y= 5) - normals point down
	-5.0f, 5.0f, -5.0f,		0.0f, -1.0f, 0.0f,	0.0f, 0.0f, //4
	5.0f, 5.0f, -5.0f,		0.0f, -1.0f, 0.0f,	1.0f, 0.0f, //5
	5.0f, 5.0f, 5.0f,		0.0f, -1.0f, 0.0f,	1.0f, 1.0f, //6
	-5.0f, 5.0f, 5.0f,		0.0f, -1.0f, 0.0f,	0.0, 1.0f, //7

	// Front wall (z = 5) - normals point toward negative z
	-5.0f, 0.0f, 5.0f,		0.0f, 0.0f, -1.0f,	0.0f, 0.0f, //8
	5.0f, 0.0f, 5.0f,		0.0f, 0.0f, -1.0f,	1.0f, 0.0f, //9
	5.0f, 5.0f, 5.0f,		0.0f, 0.0f, -1.0f,	1.0f, 1.0f, //10
	-5.0f, 5.0f, 5.0f,		0.0f, 0.0f, -1.0f,	0.0, 1.0f, //11

	// Back Wall (z = -5) - normals point toward positive z (inward)
	-5.0f, 0.0f, -5.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f, //12
	5.0f, 0.0f, -5.0f,		0.0f, 0.0f, 1.0f,	1.0f, 0.0f, //13
	5.0f, 5.0f, -5.0f,		0.0f, 0.0f, 1.0f,	1.0f, 1.0f, //14
	-5.0f, 5.0f, -5.0f,		0.0f, 0.0f, 1.0f,	0.0, 1.0f, //15

	// Left Wall (x = -5) - normals toward positive x 
	-5.0f, 0.0f, -5.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f, //16
	-5.0f, 0.0f, 5.0,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f, //17
	-5.0f, 5.0f, 5.0f,		1.0f, 0.0f, 0.0f,	1.0f, 1.0f, //18
	-5.0f, 5.0f, -5.0f,		1.0f, 0.0f, 0.0f,	0.0, 1.0f, //19


	//Right wall (x = 5) normals toward negative x
	5.0f, 0.0f, -5.0f,		-1.0f, 0.0f, 0.0f,	0.0f, 0.0f, //20
	5.0f, 0.0f, 5.0f,		-1.0f, 0.0f, 0.0f,	1.0f, 0.0f, //21
	5.0f, 5.0f, 5.0f,		-1.0f, 0.0f, 0.0f,	1.0f, 1.0f, //22
	5.0f, 5.0f, -5.0f,		-1.0f, 0.0f, 0.0f,	0.0, 1.0f //23

	





};

const unsigned int Room::indices[36]
{
	//floor
	0, 1, 2,	2, 3, 0,
	//Ceiling
	4, 5, 6,	6, 7, 4,
	//Front Wall
	8, 9, 10,	10, 11, 8,
	//Back wall
	12, 13, 14,	14, 15, 12,
	//Left WalL;
	16, 17, 18,	18, 19, 16,
	//Right Wall
	20, 21, 22,	22, 23, 20


};


Room::Room() : VAO(0), VBO(0), EBO(0)
{
	generateBuffers();
	setupBuffers();
}
Room::~Room()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
}

void Room::generateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

void Room::setupBuffers()
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


void Room::setVertexAttribs() const
{
	////Assummin the shader uses location 0 for the position attribute.
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	// Attribute 0: position (first 3 floats)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Attribute 1: normal (next 3 floats)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//Attribute 2: texture coordinates (last 2 floats)
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}
void Room::draw() const
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


