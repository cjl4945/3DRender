#pragma once
#include <GL/glew.h>
#include "main.h"

using namespace std;

//cube vertex position centered at origin 
float verticies[] = {
	-0.5f, 0.5f, -0.5f, //Vertex 0
	0.5f, -0.5f, -0.5f, //Vertex 1
	0.5f, 0.5f, -0.5f, //Vertex 2
	-0.5f, 0.5f, -0.5f, //Vertex 3
	-0.5f, -0.5f, 0.5f, //Vertex 4
	0.5f, -0.5f, 0.5f, //Vertex 5
	0.5f, 0.5f, 0.5f, //Vertex 6
	-0.5f, 0.5f, 0.5f, //Vertex 7 
};

//Indicies for the 12 triangles of a cube
unsigned int indices[] = { 
	0,1,2,	2,3,0, //Back face 
	4,5,6,	6, 7, 4, //Front face
	0,4,7,	7,3,0, //Left face
	1,5,6,	6,2,1, // Right face
	3,2,6,	6,7,3,	//Top Face
	0,1,5,	5,4,0 //Bottom face

};

//A vertex array object (VAO) to store the configuration for vertex data
//A vertex buffer object (VBO) to store the vertex postions on the GPU
//An Element Buffer Object (EBO) to store our indices
unsigned int VAO, VBO, EBO;

void generateIdentifiers();


