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
	assert(boardPos.GetX() >= 0 && boardPos.GetX() < width
		   && boardPos.GetY() >= 0 && boardPos.GetY() < height); //If assertion triggers : x or y out of range
	content[boardPos.GetY() * width + boardPos.GetX()] = type;
}

void Board::DrawCell(Vec2<int> boardPos, Color c) const
{
	//Calculate the position of the cell on the screen
	//Start from the topleft of the board (we also add cell radius because we draw circles from the center)
	Vec2<int> pos = topLeftScreenPos + cellRadius;
	//Add the required distance depending on the cell's position in the board
	pos += boardPos * cellRadius * 2;
	//Draw the cell and take the padding into account
	raycpp::DrawCircle(pos,
		cellRadius - cellPadding,
		c);
}

void Board::DrawCell(Vec2<int> boardPos) const
{
	DrawCell(boardPos, GetCellColor(content[boardPos.Map2DTo1D(width)]));
}

int Board::GetWidth() const
{
	return width;
}

void Board::DrawCellOutline(Vec2<int> boardPos, Color c) const
{
	//Calculate the position of the cell on the screen
	Vec2<int> pos = topLeftScreenPos + cellRadius;
	//Add the required distance depending on the cell's position in the board
	pos += boardPos * cellRadius * 2;
	//Draw the cell outline
	raycpp::DrawRing(pos,cellRadius - settings::padding, cellRadius,0,360,0,c);
}

int Board::GetHeight() const
{
	return height;
}

CellType Board::GetCellType(Vec2<int> boardPos) const
{
	assert(boardPos.GetX() >= 0 && boardPos.GetX() < width
		&& boardPos.GetY() >= 0 && boardPos.GetY() < height); //If assertion triggers : x or y out of range
	return content[boardPos.Map2DTo1D(width)];
}

void Board::Draw() const
{
	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			DrawCell({x,y});
		}
	}
}

Color Board::GetCellColor(CellType celltype) const
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

