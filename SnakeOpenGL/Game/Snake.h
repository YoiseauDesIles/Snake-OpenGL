#pragma once

#include <vector>
#include <array>
#include "Case.h"
#include "Utils.h"


class Snake
{
private:
	std::vector<Case*> m_snake;
	bool m_eating = false;
	Case* m_eatingFruitCoords = nullptr;

public:
	Snake();

	void move(direction dir, std::array<std::array<Case, 20>, 20>& gameBoard);
	void eat(Case* fruit);
	void addSnakeCase(Case* boardCase);

	std::vector<vec2>& getSnakeCoords() const;
	vec2 getSnakeHeadCoord() const;
};

