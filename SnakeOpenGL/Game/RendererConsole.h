#pragma once

#include<iostream>
#include <array>
#include <string>
#include <map>
#include "GameBoard.h"
#include "Case.h"


class RendererConsole
{
private:
	std::map<caseStatus, std::string> m_mapStatus =
	{
		{caseStatus::EMPTY, "-"},
		{caseStatus::SNAKE, "0"},
		{caseStatus::FRUIT, "A"}
	};

public:
	RendererConsole();
	void draw(GameBoard& grid) const;
	void drawGameOver() const;

	friend std::ostream& operator<<(std::ostream& os, const RendererConsole& render);

};

