#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Typedefs.h"
#include "stb_image.h"

unsigned int loadPNG(std::string name) {
	stbi_set_flip_vertically_on_load(true);
	int width, height, numChannels;
	uchar* imageData;
	uint texture;
	glGenTextures(1, &texture); //generate texture
	glBindTexture(GL_TEXTURE_2D, texture); //bind texture
	std::string path = "C:/Users/yuval/Desktop/C++/3D-Testing/GLFW testing/Sprites/" + name + ".png";
	imageData = stbi_load(path.c_str(), &width, &height, &numChannels, 0); //load image /w path
	if (imageData) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData); //get a 2d image of texture
		glGenerateMipmap(GL_TEXTURE_2D); //generate mipmap of texture
	}
	else {
		std::cout << path << " did not load correctly!\n";
	}
	glBindTexture(GL_TEXTURE_2D, 0); //unbind texture
	stbi_image_free(imageData);
	return texture;
}

void prepareTextures(uint count, uint* texture) {
	glGenTextures(count, texture);
	for (int i = 0; i < count; i++) {
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //sets to repeat the picture on x axis
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //sets to repeat the picture on y axis
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //sets settings for blurring during magnification and minimization of picture
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  //sets settings for blurring during magnification and minimization of picture
	}
}