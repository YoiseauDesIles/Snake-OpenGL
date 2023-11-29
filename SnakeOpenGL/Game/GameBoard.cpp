#include "GameBoard.h"
#include "Utils.h"

GameBoard::GameBoard()
{
	vec2 currCasePos;

	for (uint8_t i = 0; i <= GRID_HEIGHT - 1; i++)
	{
		for (uint8_t j = 0; j <= GRID_WIDTH - 1; j++)
		{
			m_Grid[i][j] = Case({ j, i });
		}
	}



	/* generate secret number between 1 and 10: */
	std::vector<vec2> snakeCoords;
	vec2 initSnakeCoords = { GameBoard::getBoardHeight() / 2 , GameBoard::getBoardWidth() / 2 };
	snakeCoords.push_back(initSnakeCoords);
	m_Grid[initSnakeCoords.posY][initSnakeCoords.posX].setSnake();
	m_snake.addSnakeCase(&m_Grid[initSnakeCoords.posY][initSnakeCoords.posX]);

	//v.insert(test);
	vec2 fruitCoords = generateRandomCoords(0, GRID_WIDTH-1, snakeCoords);
	m_Grid[fruitCoords.posY][fruitCoords.posX].setFruit();

	


}
