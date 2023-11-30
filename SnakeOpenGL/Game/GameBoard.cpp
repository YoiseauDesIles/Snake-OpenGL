#include "GameBoard.h"


GameBoard::GameBoard()
{

	//m_snake = Snake();

	for (uint8_t i = 0; i <= GRID_HEIGHT - 1; i++)
	{
		for (uint8_t j = 0; j <= GRID_WIDTH - 1; j++)
		{
			m_Grid[i][j] = Case({ i, j });
		}
	}


	/* generate secret number between 1 and 10: */
	//std::vector<vec2> snakeCoords;
	//vec2 initSnakeCoords = { GameBoard::getBoardHeight() / (uint8_t)2 , GameBoard::getBoardWidth() / (uint8_t)2 };
	//snakeCoords.push_back(initSnakeCoords);
	//m_Grid[initSnakeCoords.posX][initSnakeCoords.posY].setSnake();
	//m_snake.addSnakeCase(&m_Grid[initSnakeCoords.posX][initSnakeCoords.posY]);
	//m_snake.addSnakeCase(&m_Grid[initSnakeCoords.posX + 1][initSnakeCoords.posY]);
	//m_snake.addSnakeCase(&m_Grid[initSnakeCoords.posX + 1][initSnakeCoords.posY + 1]);

	//v.insert(test);


}

void GameBoard::updateCase(vec2 coords, caseStatus status)
{
	m_Grid[coords.posX][coords.posY].setCaseStatus(status);
}

void GameBoard::updateCaseSnake(vec2 coords)
{
	m_Grid[coords.posX][coords.posY].setCaseStatus(caseStatus::SNAKE);
}

void GameBoard::updateCaseFruit(vec2 coords)
{
	m_Grid[coords.posX][coords.posY].setCaseStatus(caseStatus::FRUIT);
}




