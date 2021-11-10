#include "DFSRobot.h"
#include <assert.h>
#include "raylibCpp.h"
#include "Settings.h"

DFSRobot::DFSRobot(Board& board, Vec2<int> robotPos)
	:
	board(board),
	currentPos(robotPos)
{
	graph.resize(board.GetWidth() * board.GetHeight());
	positionsStack.push(robotPos);
}

bool DFSRobot::IsPositionValid(Vec2<int> position) const
{
	//If the cell is out of bounds.
	if (position.GetX() < 0 || position.GetX() >= board.GetWidth()
		|| position.GetY() < 0 || position.GetY() >= board.GetHeight())
		return false;
	//If the cell is a wall.
	if (board.GetCellType(position) == CellType::wall)
		return false;
	//If the cell has already been visited.
	if (graph[position.Map2DTo1D(board.GetWidth())].visited)
		return false;

	//Otherwise, the cell is valid and can be moved to.
	return true;
}

bool DFSRobot::IsFinished() const
{
	return (positionsStack.empty() || bFoundObjective);
}

bool DFSRobot::HasFoundObjective() const
{
	assert(IsFinished());//If assertion triggers: The robot has not yet finished the algorithm, cannot tell if objective will be found or not.
	return bFoundObjective;
}

void DFSRobot::Next()
{
	assert(!IsFinished());//If assertion triggers: The robot has already finished the algorithm, cannot go further.
	currentPos = positionsStack.top();
	positionsStack.pop();
	//Mark the node at the current position as visited.
	graph[currentPos.Map2DTo1D(board.GetWidth())].visited = true;
	//Check if the current position is the objective.
	if (board.GetCellType(currentPos) == CellType::objective)
	{
		//We found the objective.
		bFoundObjective = true;
	}
	else
	{
		//Push all the valid adjacent cells to the stack.
		for (int i = 0; i < 4; ++i)
		{
			//Get the position of the adjacent cell.
			Vec2<int> adjacentPos = currentPos + Vec2{directionX[i],directionY[i]};
			//Check if it's a valid cell.
			if (IsPositionValid(adjacentPos))
			{
				//Add it to the stack.
				positionsStack.push(adjacentPos);
				//Add the parent (this position) to the adjacent nodes so that we can trace back once we are done.
				graph[adjacentPos.Map2DTo1D(board.GetWidth())].parent = currentPos;
			}
		}
	}
}

void DFSRobot::DrawRobot() const
{
	board.DrawCell(currentPos,settings::robotColor);
}

