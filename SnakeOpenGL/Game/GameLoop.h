#pragma once

#include <iostream>
#include <time.h>
#include "Renderer.h"
#include "GameBoard.h"
#include "GameMechanics.h"

class GameLoop
{
private:
	uint8_t FPS;
	Renderer m_renderer;
	GameBoard m_gameBoard;
	GameMechanics m_gameMechanics;

	bool m_isRunning;
	uint8_t m_frameCnt;

public:
	GameLoop() = default;
	GameLoop(uint8_t FPS);
	~GameLoop() = default;

	void startGame();
};

