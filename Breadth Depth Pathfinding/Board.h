#pragma once
#include <vector>
#include "raylibCpp.h"
#include "Vec2.h"

enum class CellType
{
	empty,
	wall,
	objective
};

class Board
{
public:
	Board(Vec2<int> widthHeight, Vec2<int> topLeftScreenPos, int cellRadius, int cellPadding);
	void SetCell(Vec2<int> boardPos, CellType type);
	void DrawCell(Vec2<int> boardPos);
	void Draw();
private : 
	Color GetCellColor(CellType celltype);

private:
	std::vector<CellType> content;
	const int width;
	const int height;
	const int cellRadius;
	const int cellPadding;
	Vec2<int> topLeftScreenPos;

};