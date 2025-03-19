#pragma once

#include <GL/glew.h>
#include <glm.hpp>
#include <vector>
#include <iostream>




class Room
{
public:
	Room(const glm::vec3& position, const glm::vec3& size);
	~Room();
	void draw() const;

	//Room Boundary Limits
	glm::vec3 getMinBounds() const;
	glm::vec3 getMaxBounds() const;


private:
	void generateBuffers();
	void setupBuffers();
	void setVertexAttribs() const;

	GLuint VAO, VBO, EBO;
	glm::vec3 position;  //Room position in the world space
	glm::vec3 size;	//width, height, depth

	std::vector<float> vertices;

	std::vector<unsigned int> indices;
};

