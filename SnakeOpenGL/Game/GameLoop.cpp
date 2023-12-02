#include "GameLoop.h"

GameLoop::GameLoop() : FPS(60)
{
	m_gameBoard = GameBoard();
	m_gameMechanics = GameMechanics(&m_gameBoard);
}

GameLoop::GameLoop(uint8_t fps): FPS(fps)
{
	m_gameBoard = GameBoard();
	m_gameMechanics = GameMechanics(&m_gameBoard);
}

void GameLoop::startGame(GLFWwindow* window)
{

	clock_t t1, t2;
	m_isRunning = true;
	double period = 1000 / FPS; //16 ms

	m_frameCnt = 0;
    direction prevDir = direction::UP;

	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

	while (m_isRunning)
	{
		t1 = clock();

		//Wait for frame
		do {
			t2 = clock();
		} while (t2 - t1 < period);


		m_frameCnt++;
		if (m_frameCnt % 30 == 0) {
            
			glfwSwapBuffers(window);

			glfwPollEvents();

			m_gameMechanics.onUpdate(direction::DOWN);
			m_gameMechanics.onRender();

            /*if (m_gameMechanics.isGameOver()) {
                m_isRunning = false;
                //m_renderer.drawGameOver();
            }else
			    //m_renderer.draw(m_gameBoard);*/

			m_frameCnt = 0;
		}

	}

}


   


