#pragma once

#include<iostream>
#include <array>
#include <string>
#include <map>
#include "GameBoard.h"
#include "Case.h"




class Renderer
{
private:
	std::map<caseStatus, std::string> m_mapStatus =
	{
		{caseStatus::EMPTY, "-"},
		{caseStatus::SNAKE, "0"},
		{caseStatus::FRUIT, "A"}
	};

public:
	Renderer();
	void draw(const GameBoard& grid) const;

	friend std::ostream& operator<<(std::ostream& os, const Renderer& render);

};

