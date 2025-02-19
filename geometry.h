#pragma once
#include <GL/glew.h>
#include "main.h"





//cube vertex position centered at origin 
static const float vertices[24];

//Indicies for the 12 triangles of a cube
static const unsigned int indices[36];

//A vertex array object (VAO) to store the configuration for vertex data
//A vertex buffer object (VBO) to store the vertex postions on the GPU
//An Element Buffer Object (EBO) to store our indices
extern unsigned int VAO, VBO, EBO;

void generateIdentifiers();


