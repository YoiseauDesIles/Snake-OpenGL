#pragma once

#include "GameBoard.h"
#include "Utils.h"
#include "Snake.h"
#include "GameRenderer.h"

class GameMechanics
{
private:
	GameBoard* m_gameBoard;
	bool m_gameIsOver = false;
	Snake* m_snake;
	GameRenderer m_renderer;

public:
	GameMechanics() = default;
	GameMechanics(GameBoard* gameBoard);

	void onUpdate(direction dir);
	void onRender(GLFWwindow* window);
	
	void initGame();
	void checkGameCase();
	void generateNewFruit();
	bool isGameOver() const { return m_gameIsOver; }
};

