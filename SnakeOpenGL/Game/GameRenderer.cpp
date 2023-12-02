#include "GameRenderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


GameRenderer::GameRenderer(float width, float height):
	m_windowWidth(width), m_windowHeight(height),
	m_ProjectionMatrix(glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f)),
	m_ViewMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
{
	initRenderer();
}

void GameRenderer::initRenderer()
{
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GLCall(glEnable(GL_BLEND));

	const size_t maxQuadCount = static_cast<size_t>(GameBoard::getBoardHeight() * GameBoard::getBoardWidth());
	const size_t maxVertexCount = maxQuadCount * 4;
	const size_t maxIndexCount = maxQuadCount * 6;


	m_VertexArray = std::make_unique<VertexArray>();
	m_VertexBuffer = std::make_unique<VertexBuffer>(nullptr, maxVertexCount * sizeof(Vertex), true);

	m_layout.push<float>(2); //Coords
	m_layout.push<float>(4); //Color

	std::vector<uint32_t> indices = initIndices(maxIndexCount);

	m_VertexArray->addBuffer(*m_VertexBuffer, m_layout);
	m_IndexBuffer = std::make_unique<IndexBuffer>(indices, sizeof(indices));
	
	m_Shader = std::make_unique<Shader>("Game/ressources/shaders/Basic.shader");
	m_Shader->bind();
	m_Shader->setUniform4f("u_Color", 0.9f, 0.8f, 0.8f, 1.0f);
}

std::vector<uint32_t> GameRenderer::initIndices(const size_t& maxIndexCount)
{
	std::vector<uint32_t> indices;
	uint32_t offset = 0;
	for (size_t i = 0; i < maxIndexCount; i += 6)
	{
		indices.push_back(0 + offset);
		indices.push_back(1 + offset);
		indices.push_back(2 + offset);
		
		indices.push_back(2 + offset);
		indices.push_back(3 + offset);
		indices.push_back(0 + offset);

		/*indices[i + 0] = 0 + offset;
		indices[i + 1] = 1 + offset;
		indices[i + 2] = 2 + offset;

		indices[i + 3] = 2 + offset;
		indices[i + 4] = 3 + offset;
		indices[i + 5] = 0 + offset;*/

		offset += 4;
	}
}

Vertex* GameRenderer::createQuad(Vertex* target, float x, float y)
{
	float quadWidth = m_windowWidth / GameBoard::getBoardWidth();
	float quadHeight = m_windowHeight / GameBoard::getBoardHeight();

	x *= quadWidth;
	y *= quadHeight;




}


void GameRenderer::drawConsole(GameBoard& gameBoard) const
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

void GameRenderer::drawGameOver() const
{
	system("cls");
	std::cout << "Game over" << "\n";
}



std::ostream& operator<<(std::ostream& stream, const GameRenderer& other)
{
	std::string joinString = "";
	
	stream << joinString;
	return stream;
}