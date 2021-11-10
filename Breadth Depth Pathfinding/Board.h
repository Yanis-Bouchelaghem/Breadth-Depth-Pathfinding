#pragma once
#include <vector>
#include "raylibCpp.h"
#include "Vec2.h"

//Represents what a cell can contain
enum class CellType
{
	empty,
	wall,
	objective
};

//A class that represents the play field, handles the content of the board and its display.
class Board
{
public:
	Board(Vec2<int> widthHeight, Vec2<int> topLeftScreenPos, int cellRadius, int cellPadding);
	void SetCell(Vec2<int> boardPos, CellType type);
	void DrawCell(Vec2<int> boardPos, Color c) const;
	void DrawCell(Vec2<int> boardPos) const;
	void Draw() const;
	int GetWidth() const;
	int GetHeight() const;
	CellType GetCellType(Vec2<int> boardPos) const;
private : 
	Color GetCellColor(CellType celltype) const;

private:
	std::vector<CellType> content;
	const int width;
	const int height;
	const int cellRadius;
	const int cellPadding;
	const Vec2<int> topLeftScreenPos;

};