#pragma once

#include <iostream>
#include <time.h>
#include "RendererConsole.h"
#include "GameBoard.h"
#include "GameMechanics.h"
#include "Snake.h"

class GameLoop
{
private:
	uint8_t FPS;
	RendererConsole m_renderer;
	GameBoard m_gameBoard;
	GameMechanics m_gameMechanics;
	//Snake m_snake;

	bool m_isRunning;
	uint8_t m_frameCnt;

public:
	GameLoop() = default;
	GameLoop(uint8_t FPS);
	~GameLoop() = default;

	void startGame();
	direction getKeyboardInput(direction previousDir);
};

