#define STB_IMAGE_IMPLEMENTATION
#define STBI_ASSERT
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <random>
#include <chrono>
#include <cmath>
#include <vector>
#include "Typedefs.h"
#include "Time.h"
#include "Shaders.h"
#include "stb_image.h"
#include "TextureLoader.h"
#include "Rectangle.h"
#include "Cube.h"

const int tickrate = 120;
const double timePerCycle = (1000.0/tickrate) * 1e6;
const int windowWidth  = 1400;
const int windowHeight = 1400;
const int gridWidth = 16;
const int gridHeight = 16;
bool ready;
const double PI = 3.14159265358979;

size_t scene = 0;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mod);

int main() {
	//initiate glfw and make it use the correct openGL version
	//currently 4.6; might alter this at some point to allow more devices
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	//create window
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "test window", NULL, NULL);
	
	//ensure window was created correctly before proceeding, and termiate program if it wasn't.
	if (window == NULL) {
		std::cout << "Failed to create window!\n";
		glfwTerminate();
		return -1;
	}

	//make the window current, and set function to be called when window is resized (resizes the window to match) 
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, keyCallback);

	//ensure GLAD was loaded correctly, and terminate program if it wasn't.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD!\n";
		return -1;
	}
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND); //enable transparent object rendering
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //configure transparent object rendering
	Shader textureProgram("C:/Users/yuval/Desktop/C++/GLSL/3D Texture Shader/VertexShader.txt", "C:/Users/yuval/Desktop/C++/GLSL/3D Texture Shader/FragmentShader.txt", "Texture Shader");

	textureProgram.use();

	//view matrix; functions as transformation for the camera, but is in reality transforming every other object. 
	//thus to move camera right, decrease x (to move everything else left), making it appear as though camera moved right.
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
	textureProgram.setMatrix("view", viewMatrix);

	//projection matrix; used to set the coordinates of clip space, and simulates the effect of perspective.
	glm::mat4 projectionMatrix = glm::mat4(1.0f);
	projectionMatrix = glm::perspective(glm::radians(45.0f), (float)windowWidth/(float)windowHeight, 0.1f, 100.0f);
	textureProgram.setMatrix("projection", projectionMatrix);

	Cube* tester = new Cube(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f, 2.0f), 0.0f, "Thingy", &textureProgram);
	tester->rotationVec = glm::vec3(1.0f, 1.0f, 1.0f);

	glClearColor(0.4f, 0.8f, 1.0f, 0.0f);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution dis(-0.01, 0.01);
	glm::vec3 velocity = glm::vec3(dis(gen), dis(gen), dis(gen));
	float k = 1;
	std::cout << "Press space to start! " << std::endl;
	//render loop; does things that should happen every frame; might make this have a recursive call(or just put "update()" in here), useful for hooks, currently unsure
	while (!glfwWindowShouldClose(window)) {
		std::chrono::steady_clock::time_point timeStart = curTime(); //this is the timestamp of an update starting
		processInput(window); //process input

		glClear(GL_COLOR_BUFFER_BIT); //clear information left from previous frame
		glClear(GL_DEPTH_BUFFER_BIT);


		tester->rotation += glm::radians(0.5f);

		//set k equal to the scene so the user can accelerate the box
		k = scene;
		tester->translation += velocity * k;
		
		if (tester->translation.x >= 1.0f + abs(tester->translation.z) * tan(glm::radians(22.5f)))
			velocity.x = -abs(velocity.x);
		else if (tester->translation.x <= -1.0f - abs(tester->translation.z) * tan(glm::radians(22.5f)))
			velocity.x = abs(velocity.x);
		else if (tester->translation.y >= 1.0f + abs(tester->translation.z) * tan(glm::radians(22.5f)))
			velocity.y = -abs(velocity.y);
		else if (tester->translation.y <= -1.0f - abs(tester->translation.z) * tan(glm::radians(22.5f)))
			velocity.y = abs(velocity.y);
		else if (tester->translation.z >= 0.0f)
			velocity.z = -abs(velocity.z);
		else if (tester->translation.z <= -20.0f)
			velocity.z = abs(velocity.z);
		
		tester->draw();

		glfwSwapBuffers(window); //swap the buffers
		glfwPollEvents(); //process events
		
		//wait if not enough time has passed between frames
		double timeInCycle = (curTime() - timeStart).count() / 1e6;
		if (timeInCycle < timePerCycle)
			preciseSleep((timePerCycle / 1e6) - timeInCycle); //sleep for remainder of time
	}
	glfwTerminate(); //terminate openGL elements correctly
	return 0; //terminate main()
}

//resize view when the window is resized. this should also called when the context is made current.
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

//processes keyboard inputs; add more statements to check more keys; should make this a switch statement maybe, since that's faster. 
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		//modify translation value. how???? 
		//can make player global; awful solution
		//can make a register of objects global, and insert player? bad solution but probably not as bad?
		//not sure it's even possible to pass player into this function, so thats not a great idea
		//no clue adofhpsdoihfa;lsjdnvsdlbijhoadfqpejfuihwefgskjf
		ready = 1;
	}
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mod) {
	switch(key){
	case GLFW_KEY_SPACE:
		if (action == GLFW_PRESS) {
			scene++;
			std::cout << "Speed factor: " << scene << '\n';
		}
		break;
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, true);
		break;
	}
}