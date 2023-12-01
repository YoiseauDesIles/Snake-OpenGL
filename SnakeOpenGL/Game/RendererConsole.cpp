#include "RendererConsole.h"


RendererConsole::RendererConsole()
{
}

void RendererConsole::draw(GameBoard& gameBoard) const
{

	std::map<caseStatus, std::string> mapStatus =
	{
		{caseStatus::EMPTY, "-"},
		{caseStatus::SNAKE, "S"},
		{caseStatus::FRUIT, "F"}
	};

	std::string joinString = "";
	auto grid = gameBoard.getGrid();

	for (int i = 0; i <= GameBoard::getBoardHeight() - 1; i++)
	{
		for (int j = 0; j <= GameBoard::getBoardWidth() - 1; j++) 
		{
			joinString += mapStatus[grid[j][i].getCaseStatus()];
		}
		joinString += "\n";

	}

	system("cls");
	std::cout << joinString << "\n";

}

void RendererConsole::drawGameOver() const
{
	system("cls");
	std::cout << "Game over" << "\n";
}



std::ostream& operator<<(std::ostream& stream, const RendererConsole& other)
{
	std::string joinString = "";
	
	stream << joinString;
	return stream;
}