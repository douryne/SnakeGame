#pragma once

#include "Location.h"
#include "Graphics.h"
#include <random>

class Board
{
public:
	enum class CellContents
	{
		Empty,
		Obstacle,
		Food,
		Poison
	};
public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c);
	int GetWidth() const;
	int GetHeight() const;
	bool IsInTheBoard(const Location& loc) const;
	void DrawBorder();
	void ConsumeContents(const Location& loc);
	CellContents GetContents(const Location& loc) const;
	void SpawnContents(std::mt19937& rng, const class Snake& snake, CellContents contentsType);
	void DrawCells();
private:
	static constexpr int cellPadding = 1;
	static constexpr Color borderColor = Colors::White;
	static constexpr Color obstacleColor = Colors::White;
	static constexpr Color foodColor = Colors::Red;
	static constexpr Color poisonColor = {64, 8, 64};
	static constexpr int width = 20;
	static constexpr int height = 20;
	int dimension = 25;
	static constexpr int borderWidth = 5;
	static constexpr int borderPadding = 1;
	CellContents contents[width * height] = { CellContents::Empty };
	int x = 140;
	int y = 45;
	Graphics& gfx;
};