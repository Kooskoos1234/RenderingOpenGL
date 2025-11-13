#ifndef CUBE_H
#define CUBE_H

#include <string>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shaders.h"
#include "TextureLoader.h"

typedef unsigned int uint;

class Cube {
	static float vertices[60];
	//uint* indices = new uint[]{
	//	//front 
	//	0, 1, 2,
	//	1, 2, 3,

	//	//back
	//	4, 5, 6,
	//	5, 6, 7,

	//	//top
	//	1, 3, 5,
	//	3, 5, 7,

	//	//bottom
	//	0, 2, 4,
	//	2, 4, 6,

	//	//left
	//	0, 1, 8,
	//	1, 8, 9,

	//	//right
	//	2, 3, 10,
	//	3, 10, 11
	//};

	static uint indices[36];
	uint VAO, VBO, EBO;
	uint texture;
	std::string imageName;
	Shader* shader;

public:

	glm::vec3 translation;
	glm::vec3 scaling;
	glm::vec3 rotationVec;
	float rotation;

	/*Base rectangle constructor.
	* The rectangles created by this, before transformation, are positioned at 0.0f, 0.0f, 0.0f, have a scale of 0.2f, 0.2f, 0.2f (TOTAL) and rotation of 0 radians
	*
	* @param[in] translation: The translation to be initially used for the cube
	* @param[in] scale: The scale to be initially used for the cube
	* @param[in] rotation: The rotation (in radianas) to be initially used for the cube
	* @param[in] imageName: The name of the image to be used as the cube's texture
	* @param[in] shader: The shader program to be used to render the cube.*/
	Cube(glm::vec3 translation, glm::vec3 scale, float rotation, std::string imageName, Shader* shader);

	//default constructor; sets all to null or irrelevent values; exists so arrays can be created.
	Cube();
	//destructor to clean up dynamic objects (and possibly do other stuff later :)  )
	~Cube();
	//use shader program, apply matrix transformations, set texture units, and render cube.
	void draw();
};

#endif