#include "GameRenderer.h"

#include "GLFW/glfw3.h"

Vertex* createQuad2(Vertex* target, float x, float y)
{
	float size = 100.0f;
	x *= 100.0f;
	y *= 100.0f;

	target->position = { x ,y };
	target->color = { 0.8, 0.1, 0.5, 1.0 };
	target++;

	target->position = { x + size, y };
	target->color = { 0.8, 0.1, 0.5, 1.0 };
	target++;

	target->position = { x + size,  y + size };
	target->color = { 0.8, 0.1, 0.5, 1.0 };
	target++;

	target->position = { x,  y + size };
	target->color = { 0.8, 0.1, 0.5, 1.0 };
	target++;

	return target;
}


GameRenderer::GameRenderer(float width, float height):
	m_windowWidth(width), m_windowHeight(height),
	m_ProjectionMatrix(glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f)),
	m_ViewMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
	m_TranslationMatrix(0, 0, 0)
{
	m_renderer = Renderer();
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
	/*std::vector<uint32_t> indices;
	std::array<uint32_t, 2400> indices2;
	uint32_t offset = 0;
	for (size_t i = 0; i < maxIndexCount; i += 6)
	{
		indices.push_back(0 + offset);
		indices.push_back(1 + offset);
		indices.push_back(2 + offset);

		indices.push_back(2 + offset);
		indices.push_back(3 + offset);
		indices.push_back(0 + offset);

		indices2[i + 0] = 0 + offset;
		indices2[i + 1] = 1 + offset;
		indices2[i + 2] = 2 + offset;

		indices2[i + 3] = 2 + offset;
		indices2[i + 4] = 3 + offset;
		indices2[i + 5] = 0 + offset;
		
		offset += 4;
	}*/

	m_VertexArray->addBuffer(*m_VertexBuffer, m_layout);
	m_IndexBuffer = std::make_unique<IndexBuffer>(indices.data(), indices.size()* sizeof(uint32_t));
	
	m_Shader = std::make_unique<Shader>("Game/Ressources/Shaders/Basic.shader");
	m_Shader->bind();
	m_Shader->setUniform4f("u_Color", 0.5f, 0.1f, 0.8f, 1.0f);

	initVertices();
	
	m_VertexBuffer->bind();

	GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices.size() * sizeof(Quad), m_vertices.data()));

	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));

	glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), m_TranslationMatrix);
	glm::mat4 MVPMatrix = m_ProjectionMatrix * m_ViewMatrix * modelMatrix;
	m_Shader->bind();
	m_Shader->setUniformMat4f("u_MVP", MVPMatrix);

	m_renderer.draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);

}

void GameRenderer::initRenderer2()
{
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GLCall(glEnable(GL_BLEND));

	const size_t maxQuadCount = 1000;
	const size_t maxVertexCount = maxQuadCount * 4;
	const size_t maxIndexCount = maxQuadCount * 6;

	float vertices[] =
	{
		-150.0f, -150.0f, 0.2, 0.5, 0.6, 1.0,
		150.0f,-150.0f, 0.2, 0.5, 0.6, 1.0,
		150.0f, 150.0f, 0.2, 0.5, 0.6, 1.0,
		-150.0f, 150.0, 0.2, 0.5, 0.6, 1.0
	};

	m_VertexArray = std::make_unique<VertexArray>();
	//m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 9 * 9 * sizeof(float));
	m_VertexBuffer = std::make_unique<VertexBuffer>(vertices,  4 * 6 * sizeof(float), false);
	VertexBufferLayout layout;
	layout.push<float>(2);
	layout.push<float>(4);


	unsigned int indices[] = {
		0, 1, 2, 2, 3, 0
	};

	/*uint32_t indices[maxIndexCount];
	uint32_t offset = 0;
	for (size_t i = 0; i < maxIndexCount; i += 6)
	{
		indices[i + 0] = 0 + offset;
		indices[i + 1] = 1 + offset;
		indices[i + 2] = 2 + offset;

		indices[i + 3] = 2 + offset;
		indices[i + 4] = 3 + offset;
		indices[i + 5] = 0 + offset;

		offset += 4;
	}*/

	m_VertexArray->addBuffer(*m_VertexBuffer, layout);
	m_IndexBuffer = std::make_unique<IndexBuffer>(indices, sizeof(indices));

	m_Shader = std::make_unique<Shader>("Game/Ressources/Shaders/Basic.shader");
	m_Shader->bind();
	//m_Shader->setUniform4f("u_Color", 0.9f, 0.8f, 0.8f, 1.0f);

	
	/*uint32_t indexCount = 0;

	std::array<Vertex, 1000> vertices;
	Vertex* buffer = vertices.data();

	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			buffer = createQuad2(buffer, x, y);
			indexCount += 6;
		}
	}

	m_IndexBuffer->setCount(indexCount);

	m_VertexBuffer->bind();
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data()));

	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));



	glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), m_TranslationMatrix);
	glm::mat4 MVPMatrix = m_ProjectionMatrix * m_ViewMatrix * modelMatrix;
	m_Shader->bind();
	m_Shader->setUniformMat4f("u_MVP", MVPMatrix);

	//m_renderer.draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);*/
	


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
	return indices;
}

void GameRenderer::initVertices()
{
	size_t indexCount = 0;
	int a = GameBoard::getBoardHeight();
	int b = GameBoard::getBoardWidth();
	for (int y = 0; y < GameBoard::getBoardHeight(); y++)
	{
		for (int x = 0; x < GameBoard::getBoardWidth(); x++)
		{
			m_vertices.push_back(createQuad(x, y));
			indexCount += 6;
		}
	}
	m_indexCount = indexCount+6;
	m_IndexBuffer->setCount(indexCount+6);
}

Quad GameRenderer::createQuad(float x, float y)
{
	float quadWidth = m_windowWidth / GameBoard::getBoardWidth();
	float quadHeight = m_windowHeight / GameBoard::getBoardHeight();

	x *= quadWidth;
	y *= quadHeight;
	int offset = 2.0f;

	Quad quad;
	quad.vertex1.position = { x + offset ,y + offset };
	quad.vertex1.color = { 0.2, 0.5, 0.6, 0.5 };

	quad.vertex2.position = { x + quadWidth - offset ,y + offset };
	quad.vertex2.color = { 0.1, 0.5, 0.8, 0.5 };

	quad.vertex3.position = { x + quadWidth - offset ,y + quadHeight - offset};
	quad.vertex3.color = { 0.1, 0.5, 0.8, 0.5 };

	quad.vertex4.position = { x + offset ,y + quadHeight - offset};
	quad.vertex4.color = { 0.1, 0.5, 0.8, 0.5 };

	return quad;
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

void GameRenderer::draw(GLFWwindow* window)
{
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	m_renderer.clear();

	/*uint32_t indexCount = 0;

	std::array<Vertex, 1000> vertices;
	Vertex* buffer = vertices.data();

	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			buffer = createQuad2(buffer, x, y);
			indexCount += 6;
		}
	}

	m_IndexBuffer->setCount(indexCount);
	
	m_VertexBuffer->bind();
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data()));

	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));


	*/
	m_IndexBuffer->setCount(m_indexCount);
	glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), m_TranslationMatrix);
	glm::mat4 MVPMatrix = m_ProjectionMatrix * m_ViewMatrix * modelMatrix;
	m_Shader->bind();
	m_Shader->setUniformMat4f("u_MVP", MVPMatrix);
	
	m_renderer.draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);

}



std::ostream& operator<<(std::ostream& stream, const GameRenderer& other)
{
	std::string joinString = "";
	
	stream << joinString;
	return stream;
}