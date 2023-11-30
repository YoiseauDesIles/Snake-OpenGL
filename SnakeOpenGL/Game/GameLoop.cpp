#include "GameLoop.h"

GameLoop::GameLoop(uint8_t fps): FPS(fps)
{
	m_renderer = Renderer();
	m_gameBoard = GameBoard();
	m_gameMechanics = GameMechanics(m_gameBoard);
}

void GameLoop::startGame()
{
	
	clock_t t1, t2;
	m_isRunning = true;
	double period = 1000 / FPS; //16 ms

	m_frameCnt = 0;
	int moveCnt = 0;
	while (m_isRunning)
	{
		t1 = clock();

		//Wait for frame
		do {
			t2 = clock();
		} while (t2 - t1 < period);


		m_frameCnt++;
		if (m_frameCnt % 60 == 0) {
			m_gameMechanics.move();
			m_renderer.draw(m_gameBoard);
		}

		if (m_frameCnt == 60)
		{
			moveCnt++;
			m_frameCnt = 0;
		}

		if (moveCnt >= 6)
			m_isRunning = false;

	}


}
