#include "GameMechanics.h"



GameMechanics::GameMechanics(GameBoard* gameBoard)
{
	m_gameBoard = gameBoard;
	m_snake = gameBoard->getSnake();
	initGame();
	m_renderer = GameRenderer(960.0f, 540.0f);
	
}


void GameMechanics::onUpdate(direction dir)
{
	m_snake->move(dir, *m_gameBoard);
	checkGameCase();
}

void GameMechanics::onRender(GLFWwindow* window)
{
	m_renderer.draw(window);
}



void GameMechanics::initGame()
{
	vec2 initSnakeCoords = { GameBoard::getBoardHeight() / (uint8_t)2 , GameBoard::getBoardWidth() / (uint8_t)2 };
	m_gameBoard->updateCaseSnake({ initSnakeCoords.posX, initSnakeCoords.posY });
	m_gameBoard->getSnake()->addSnakeCase(&m_gameBoard->getGrid()[initSnakeCoords.posX][initSnakeCoords.posY]);

	generateNewFruit();
	//m_gameBoard->updateCaseFruit({ 10, 7 });

}


void GameMechanics::checkGameCase()
{
	Case* snakeHead = m_snake->getSnakeHead();
	if (snakeHead->isEmpty())
		snakeHead->setSnake();
	else if (snakeHead->isFruit())
	{
		m_snake->eat(snakeHead);
		generateNewFruit();
	}
	else
		m_gameIsOver = true;
}


void GameMechanics::generateNewFruit()
{
	std::vector<vec2> snakeCoords = m_gameBoard->getSnake()->getSnakeCoords();

	vec2 fruitCoords = generateRandomCoords(0, GameBoard::getBoardWidth() - 1, snakeCoords);
	m_gameBoard->updateCaseFruit(fruitCoords);
	
	
}


