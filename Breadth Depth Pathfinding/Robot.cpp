#include "Robot.h"
#include <assert.h>
#include "Settings.h"

Robot::Robot(Board& board, Vec2<int> robotPos)
	:
	board(board),
	currentPos(robotPos)
{
	graph.resize(board.GetWidth() * board.GetHeight());
}

bool Robot::HasFoundObjective() const
{
	assert(IsFinished());//If assertion triggers: The robot has not yet finished the algorithm, cannot tell if objective will be found or not.
	return bFoundObjective;
}

void Robot::DrawRobot()
{
	board.DrawCell(currentPos, settings::robotColor);
}

void Robot::DrawVisitedOutline()
{
	for (int x = 0; x < board.GetWidth(); ++x)
	{
		for (int y = 0; y < board.GetHeight(); ++y)
		{
			if (graph[y * board.GetWidth() + x].state == NodeState::visited)
				board.DrawCellOutline({ x,y }, settings::visitedColor);
		}
	}
}

void Robot::DrawTargetedOutline()
{
	for (int x = 0; x < board.GetWidth(); ++x)
	{
		for (int y = 0; y < board.GetHeight(); ++y)
		{
			if (graph[y * board.GetWidth() + x].state == NodeState::targeted)
				board.DrawCellOutline({ x,y }, settings::targetedColor);
		}
	}
}

void Robot::DrawFinalObjectivePath()
{
	assert(bFoundObjective);//If assertion triggers: the path to the objective hasn't been found yet.
	//Draw the path and enumeration
	int length = int(finalObjectivePath.size() - 1);
	for (auto& vec : finalObjectivePath)
	{
		board.DrawCellOutline(vec, settings::objectivePathColor);
		board.DrawCellNumber(vec, length--, settings::numbersColor);
	}
}


Vec2<int> Robot::GetCurrentPosition()
{
	return currentPos;
}

bool Robot::IsPositionValid(Vec2<int> position) const
{
	//If the cell is out of bounds.
	if (position.GetX() < 0 || position.GetX() >= board.GetWidth()
		|| position.GetY() < 0 || position.GetY() >= board.GetHeight())
		return false;
	//If the cell is a wall.
	if (board.GetCellType(position) == CellType::wall)
		return false;
	//If the cell has already been visited.
	if (graph[position.Map2DTo1D(board.GetWidth())].state == NodeState::visited)
		return false;
	//Otherwise, the cell is valid and can be moved to.
	return true;
}

std::vector<Vec2<int>> Robot::CalculateFinalObjectivePath()
{
	assert(bFoundObjective);//If assertion triggers: objective hasn't been found yet, cannot calculate path.
	std::vector<Vec2<int>> path;
	//Get the node of the current position (the objective)
	const Node& node = graph[currentPos.Map2DTo1D(board.GetWidth())];
	Vec2<int> position = currentPos;
	//Trace back until we cannot find a parent anymore.
	while (position != Vec2{ -1,-1 })
	{
		path.emplace_back(position);
		position = graph[position.Map2DTo1D(board.GetWidth())].parent;
	}
	return path;
}
