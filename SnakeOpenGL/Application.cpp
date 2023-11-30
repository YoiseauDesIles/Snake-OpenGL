#include <iostream>
#include "Game/GameLoop.h"

int main(int argc, char** argv) 
{
	std::cout << "test" << "\n";

	//GameBoard game;
	//game.move();
	//Renderer renderer;
	//renderer.draw(game);

	GameLoop game(60);
	game.startGame();


	return 0;
}