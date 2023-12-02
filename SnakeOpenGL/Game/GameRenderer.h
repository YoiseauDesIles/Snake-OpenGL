#pragma once

#include<iostream>
#include <array>
#include <string>
#include <map>
#include "GameBoard.h"
#include "Case.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

struct Vec2
{
	float x, y;
};

struct Vec4
{
	float x, y, z, w;
};

struct Vertex
{
	Vec2 position;
	Vec4 color;
};

class GameRenderer
{
private:
	std::map<caseStatus, std::string> m_mapStatus =
	{
		{caseStatus::EMPTY, "-"},
		{caseStatus::SNAKE, "0"},
		{caseStatus::FRUIT, "A"}
	};

	float m_windowWidth, m_windowHeight;

	std::unique_ptr<VertexArray> m_VertexArray;
	std::unique_ptr<IndexBuffer> m_IndexBuffer;
	std::unique_ptr<Shader> m_Shader;
	std::unique_ptr<VertexBuffer> m_VertexBuffer;

	VertexBufferLayout m_layout;

	glm::mat4 m_ProjectionMatrix, m_ViewMatrix;

	void initRenderer();
	std::vector<uint32_t> initIndices(const size_t& maxIndexCount);
	Vertex* createQuad(Vertex* target, float x, float y);

public:
	GameRenderer() = default;
	GameRenderer(float width, float height);
	void drawConsole(GameBoard& grid) const;
	void drawGameOver() const;

	friend std::ostream& operator<<(std::ostream& os, const GameRenderer& render);

};

