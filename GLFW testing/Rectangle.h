#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <string>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shaders.h"
#include "TextureLoader.h"

typedef unsigned int uint;

class Rectangle {
	float* vertices;
	unsigned int* indices = new unsigned int[]{
		0, 1, 2,
		1, 2, 3
	};
	uint VAO, VBO, EBO;
	uint texture;
	std::string imageName;
	Shader* shader;

	//rework rotation to function the 3d way :< 

public:

	glm::vec3 translation;
	glm::vec3 scaling;
	glm::vec3 rotationVec;
	float rotation;
	
	/*Base rectangle constructor.
	* The rectangles created by this, before transformation, are positioned at 0.0f, 0.0f, 0.0f, have a scale of 0.2f, 0.2f, 0.2f (TOTAL) and rotation of 0 radians
	* 
	* @param[in] translation: The translation to be initially used for the rectangle
	* @param[in] scale: The scale to be initially used for the rectangle
	* @param[in] rotation: The rotation (in radianas) to be initially used for the rectangle
	* @param[in] imageName: The name of the image to be used as the rectangle's texture
	* @param[in] shader: The shader program to be used to render the rectangle.*/
	Rectangle(glm::vec3 translation, glm::vec3 scale, float rotation, std::string imageName, Shader* shader);
	
	//default constructor; sets all to null or irrelevent values; exists so arrays can be created.
	Rectangle();
	//destructor to clean up dynamic objects (and possibly do other stuff later :)  )
	~Rectangle();
	//use shader program, apply matrix transformations, set texture units, and render rectangle.
	void draw();
};

#endif