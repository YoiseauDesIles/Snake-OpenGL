#include <iostream>
#include "Game/GameBoard.h"
#include "Game/Renderer.h"

int main(int argc, char** argv) 
{
	std::cout << "test" << "\n";

	GameBoard game;
	Renderer renderer;
	renderer.draw(game);

	return 0;
}