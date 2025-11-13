#include "Rectangle.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

extern bool ready;
extern const double PI;

Rectangle::Rectangle(glm::vec3 translation, glm::vec3 scale, float rotation, std::string imageName, Shader* shader) :
	translation{ translation }, scaling{scale}, rotation{ rotation }, imageName{ imageName }, shader{ shader } {
	rotationVec = glm::vec3(0.0f, 0.0f, 1.0f); //sets default rotation vector to be the z axis
	//preoare vertices
	{
		vertices = new float[]{
				-0.1f, -0.1f, 0.0f, 0.0f, 0.0f, //bottom left
				-0.1f,  0.1f, 0.0f, 0.0f, 1.0f, //top left
				 0.1f, -0.1f, 0.0f, 1.0f, 0.0f, //bottom right
				 0.1f,  0.1f, 0.0f, 1.0f, 1.0f  //top right
		};
	}

	//prepare VAO
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 20, vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * 6, indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(0));					//passes in attributes to index 0, for positions
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(3 * sizeof(float))); //passes in attributes to index 1, for texture coords

		glEnableVertexAttribArray(0); //enables attributes in index 0 (position)
		glEnableVertexAttribArray(1); //enables attributes in index 1 (texture coords)

		glBindVertexArray(0); //unbind the vertex array, for safety's sake
	}
	
	//prepare textures
	{
		prepareTextures(1, &texture);
		texture = loadPNG(imageName);
	}
}

Rectangle::Rectangle() {
	vertices = nullptr;
	shader = nullptr;
	texture = 0;
	rotation = 0.0f;
	translation = glm::vec3(0.0f, 0.0f, 0.0f);
	rotationVec = glm::vec3(0.0f, 0.0f, 0.0f);
	scaling = glm::vec3(0.0f, 0.0f, 0.0f);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

Rectangle::~Rectangle() {
	delete[] vertices;
}

void Rectangle::draw() {
	shader->use();

	glm::mat4x4 transformation = glm::mat4(1.0f);
	transformation = glm::translate(transformation, translation);
	transformation = glm::rotate(transformation, rotation, rotationVec);
	transformation = glm::scale(transformation, scaling);

	shader->setMatrix("transform", transformation);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}