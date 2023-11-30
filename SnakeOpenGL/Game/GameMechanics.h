#pragma once

#include "GameBoard.h"
#include "Snake.h"
#include "Utils.h"

class GameMechanics
{
private:
	GameBoard m_gameBoard;
	Snake m_snake;

public:
	GameMechanics();
	GameMechanics(GameBoard& gameBoard);

	void initGame();
	void move();
	void generateNewFruit();
};

