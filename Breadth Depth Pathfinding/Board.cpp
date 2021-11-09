#include "Board.h"
#include <random>
#include <assert.h>
#include "raylibCpp.h"
#include "Settings.h"

Board::Board(Vec2<int> dimensions,Vec2<int> topLeftScreenPos, int cellRadius, int cellPadding)
	:
	width(dimensions.GetX()),
	height(dimensions.GetY()),
	topLeftScreenPos(topLeftScreenPos),
	cellRadius(cellRadius),
	cellPadding(cellPadding)
{
	content.resize(dimensions.GetX() * dimensions.GetY());

}


void Board::SetCell(Vec2<int> boardPos, CellType type)
{
	content[boardPos.GetY() * width + boardPos.GetX()] = type;
}

void Board::DrawCell(Vec2<int> boardPos)
{
	Vec2<int> pos = boardPos * cellRadius * 2 + topLeftScreenPos;
	raycpp::DrawCircle(pos,
					   cellRadius - cellPadding,
					   GetCellColor(content[boardPos.GetY() * width + boardPos.GetX()]));
}

void Board::Draw()
{
	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			DrawCell({x,y});
		}
	}
}



Color Board::GetCellColor(CellType celltype)
{
	switch (celltype)
	{
	case CellType::empty:
		return settings::emptyColor;
	case CellType::wall:
		return settings::wallColor;
	case CellType::objective:
		return settings::objectiveColor;
	default:
		assert(false); //If assertion fails : given CellType doesn't exist.
	}
	return WHITE;
}

