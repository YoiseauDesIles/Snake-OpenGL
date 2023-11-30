#include "GameMechanics.h"

GameMechanics::GameMechanics()
{

}

GameMechanics::GameMechanics(GameBoard& gameBoard)
{
	m_gameBoard = gameBoard;
	m_snake = Snake();
	initGame();
}


void GameMechanics::initGame()
{
	vec2 initSnakeCoords = { GameBoard::getBoardHeight() / (uint8_t)2 , GameBoard::getBoardWidth() / (uint8_t)2 };
	m_gameBoard.updateCaseSnake({ initSnakeCoords.posX, initSnakeCoords.posY });
	m_snake.addSnakeCase(&m_gameBoard.getGrid()[initSnakeCoords.posX][initSnakeCoords.posY]);

	generateNewFruit();
}

void GameMechanics::move()
{
	auto grid = m_gameBoard.getGrid();
	m_snake.eat(nullptr);
	m_snake.move(direction::UP, grid);
}

void GameMechanics::generateNewFruit()
{
	std::vector<vec2> snakeCoords = m_snake.getSnakeCoords();

	vec2 fruitCoords = generateRandomCoords(0, GameBoard::getBoardWidth() - 1, snakeCoords);
	m_gameBoard.updateCaseFruit(fruitCoords);
	m_gameBoard.updateCaseFruit({10, 7});
	
}

