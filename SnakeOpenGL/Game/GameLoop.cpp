#include "GameLoop.h"
#include <conio.h>

GameLoop::GameLoop(uint8_t fps): FPS(fps)
{
	m_renderer = Renderer();
	m_gameBoard = GameBoard();
	//m_snake = Snake();
	m_gameMechanics = GameMechanics(&m_gameBoard);
}

void GameLoop::startGame()
{
	
	clock_t t1, t2;
	m_isRunning = true;
	double period = 1000 / FPS; //16 ms

	m_frameCnt = 0;
	int moveCnt = 0;
    direction prevDir = direction::UP;

	while (m_isRunning)
	{
		t1 = clock();

		//Wait for frame
		do {
			t2 = clock();
		} while (t2 - t1 < period);


		m_frameCnt++;
		if (m_frameCnt % 30 == 0) {
            direction newDir = getKeyboardInput(prevDir);
			m_gameMechanics.move(newDir);
            if (m_gameMechanics.isGameOver()) {
                m_isRunning = false;
                m_renderer.drawGameOver();
            }else
			    m_renderer.draw(m_gameBoard);
		}

		if (m_frameCnt == 60)
		{
			moveCnt++;
			m_frameCnt = 0;
		}

		if (moveCnt >= 20)
			m_isRunning = false;

	}


}

direction GameLoop::getKeyboardInput(direction previousDir)
{
    direction newDir = previousDir;

    char key;
    if (_kbhit()) {  // V�rifie si une touche est press�e
        key = _getch();  // Obtient la touche press�e

        // Traitement des touches sp�ciales
        switch (key) {
        case 27:  // Touche ESC
            std::cout << "Touche ESC appuy�e." << std::endl;
            break;
        case 2:  // Touche ESC
            newDir = direction::DOWN;
            std::cout << "Touche 2 appuy�e." << std::endl;
            break;
        case 5:  // Touche ESC
            newDir = direction::UP;
            std::cout << "Touche 5 appuy�e." << std::endl;
            break;
        case 1:  // Touche ESC
            newDir = direction::LEFT;
            std::cout << "Touche 1 appuy�e." << std::endl;
            break;
        case 3:  // Touche ESC
            newDir = direction::RIGHT;
            std::cout << "Touche 3 appuy�e." << std::endl;
            break;
        case 224:  // Touche sp�ciale pour les touches de direction
            if (_kbhit()) {
                key = _getch();  // Obtient la deuxi�me partie de la touche de direction

                // Traitement des touches de direction
                switch (key) {
                case 72:  // Fl�che du haut
                    newDir = direction::UP;
                    std::cout << "Fl�che du haut appuy�e." << std::endl;
                    break;
                case 80:  // Fl�che du bas
                    newDir = direction::DOWN;
                    std::cout << "Fl�che du bas appuy�e." << std::endl;
                    break;
                case 75:  // Fl�che de gauche
                    newDir = direction::LEFT;
                    std::cout << "Fl�che de gauche appuy�e." << std::endl;
                    break;
                case 77:  // Fl�che de droite
                    newDir = direction::RIGHT;
                    std::cout << "Fl�che de droite appuy�e." << std::endl;
                    break;
                default:
                    // Autre touche sp�ciale
                    break;
                }
            }
            break;
        default:
            // Autres touches
            std::cout << "Vous avez appuy� sur la touche : " << key << std::endl;
            break;
        }
    }
   

    return newDir;
}

