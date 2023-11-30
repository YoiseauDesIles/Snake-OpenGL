#include "Snake.h"


Snake::Snake()
{
	m_snake = std::vector<Case*>();

}

void Snake::move(direction dir, std::array<std::array<Case, 20>, 20>& gameBoard)
{

	uint8_t snakeLen = m_snake.size();
	m_snake.back()->emptyCase();

	if (snakeLen > 1)
	{
		for (uint8_t snakeIdx = snakeLen - 1; snakeIdx > 0; snakeIdx--)
		{
			m_snake[snakeIdx] = m_snake[snakeIdx-1];
			m_snake[snakeIdx]->setSnake();
		}
	}

	vec2 currHeadPos = m_snake.front()->getCoords();
	switch(dir) 
	{
		case direction::UP: 
			currHeadPos.posY--;
			break;
		case direction::DOWN:
			currHeadPos.posY++;
			break;
		case direction::LEFT:
			currHeadPos.posX--;
			break;
		case direction::RIGHT:
			currHeadPos.posX++;
			break;
	}

	m_snake.front() = &gameBoard[currHeadPos.posX][currHeadPos.posY];
	m_snake.front()->setSnake();

	if (m_eatingFruitCoords != nullptr && (m_snake.back()->getCoords() == m_eatingFruitCoords->getCoords()))
	{
		addSnakeCase(m_eatingFruitCoords);
		m_eatingFruitCoords = nullptr;
	}

}

void Snake::eat(Case* fruit)
{
	m_eatingFruitCoords = fruit;

}

void Snake::addSnakeCase(Case* boardCase)
{
	m_snake.push_back(boardCase);
}

std::vector<vec2>& Snake::getSnakeCoords() const
{
	std::vector<vec2> snakeCoords = std::vector<vec2>();
	for (Case* coord : m_snake)
	{
		vec2 currCoord = coord->getCoords();
		snakeCoords.push_back(currCoord);

	}
	return snakeCoords;
}

vec2 Snake::getSnakeHeadCoord() const
{
	return m_snake.front()->getCoords();
}
