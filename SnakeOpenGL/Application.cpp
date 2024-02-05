#include <iostream>
#include "Game/GameLoop.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/gtc/matrix_transform.hpp"

#include "Game/GameLoop.h"

int main(int argc, char** argv) 
{
	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(800, 800, "Snake OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(5);

	if (glewInit() != GLEW_OK) {
		std::cout << "Error" << "\n";
	}

	std::cout << glGetString(GL_VERSION) << "\n";
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GLCall(glEnable(GL_BLEND));

	GameLoop gameLoop;

	while (!glfwWindowShouldClose(window))
	{
		gameLoop.startGame(window);

	}



	//GameBoard game;
	//game.move();
	//Renderer renderer;
	//renderer.draw(game);

	//GameLoop game(60);
	//game.startGame();


	return 0;
}