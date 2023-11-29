#pragma once

#include <vector>
#include "Case.h"
#include "GameMechanics.h"
#include "GameBoard.h"

class Snake
{
private:
	std::vector<Case*> m_snake;


public:
	Snake();
	void move(direction dir);
	void addSnakeCase(Case* boardCase);
};

