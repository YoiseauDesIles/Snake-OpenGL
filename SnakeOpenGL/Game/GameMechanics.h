#pragma once

#include "GameBoard.h"
#include "Utils.h"

class GameMechanics
{
private:
	GameBoard* m_gameBoard;
	bool m_gameIsOver = false;
	


public:
	GameMechanics();
	GameMechanics(GameBoard* gameBoard);

	void initGame();
	void move(direction dir);
	void generateNewFruit();
	bool isGameOver() const { return m_gameIsOver; }
};

