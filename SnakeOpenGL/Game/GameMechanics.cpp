#include "GameMechanics.h"

GameMechanics::GameMechanics()
{

}

GameMechanics::GameMechanics(GameBoard* gameBoard)
{
	m_gameBoard = gameBoard;
	initGame();
}


void GameMechanics::initGame()
{
	vec2 initSnakeCoords = { GameBoard::getBoardHeight() / (uint8_t)2 , GameBoard::getBoardWidth() / (uint8_t)2 };
	m_gameBoard->updateCaseSnake({ initSnakeCoords.posX, initSnakeCoords.posY });
	m_gameBoard->getSnake()->addSnakeCase(&m_gameBoard->getGrid()[initSnakeCoords.posX][initSnakeCoords.posY]);

	//generateNewFruit();
	m_gameBoard->updateCaseFruit({ 10, 7 });
}

void GameMechanics::move(direction dir)
{

	Snake* snake = m_gameBoard->getSnake();
	snake->move(dir, *m_gameBoard);


	if (snake->getSnakeHeadCoord() == m_gameBoard->getFruitCoords()->getCoords()) {
		snake->eat(m_gameBoard->getFruitCoords());
		generateNewFruit();
	}

}

void GameMechanics::generateNewFruit()
{
	std::vector<vec2> snakeCoords = m_gameBoard->getSnake()->getSnakeCoords();

	vec2 fruitCoords = generateRandomCoords(0, GameBoard::getBoardWidth() - 1, snakeCoords);
	m_gameBoard->updateCaseFruit(fruitCoords);
	
	
}


