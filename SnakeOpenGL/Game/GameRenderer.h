#pragma once

#include<iostream>
#include <array>
#include <string>
#include <map>


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Renderer.h"
#include "GameBoard.h"
#include "Case.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include <memory>

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

struct Quad
{
	Vertex vertex1;
	Vertex vertex2;
	Vertex vertex3;
	Vertex vertex4;
};

class GLFWwindow;

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
	std::vector<Quad> m_vertices;

	std::unique_ptr<VertexArray> m_VertexArray;
	std::unique_ptr<IndexBuffer> m_IndexBuffer;
	std::unique_ptr<Shader> m_Shader;
	std::unique_ptr<VertexBuffer> m_VertexBuffer;

	VertexBufferLayout m_layout;
	Renderer m_renderer;
	size_t m_indexCount = 0;

	glm::mat4 m_ProjectionMatrix, m_ViewMatrix;
	glm::vec3 m_TranslationMatrix;

	void initRenderer();
	void initRenderer2();
	std::vector<uint32_t> initIndices(const size_t& maxIndexCount);
	Quad createQuad(float x, float y);
	void initVertices();

public:
	GameRenderer() = default;
	GameRenderer(float width, float height);
	void drawConsole(GameBoard& grid) const;
	void drawGameOver() const;
	Renderer* getRenderer() { return &m_renderer; }

	void draw(GLFWwindow* window);

	friend std::ostream& operator<<(std::ostream& os, const GameRenderer& render);

};

