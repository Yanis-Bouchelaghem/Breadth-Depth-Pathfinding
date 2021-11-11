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
	if (graph[position.Map2DTo1D(board.GetWidth())].state == NodeState::visited)
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
	//Find the next node to visit
	bool foundUnvisited = false;
	Vec2<int> nextPos;
	//Keep popping until we find the next unvisited node or we empty the stack.
	do
	{
		nextPos = positionsStack.top();
		positionsStack.pop();
		Node& node = graph[nextPos.Map2DTo1D(board.GetWidth())];
		if (node.state != NodeState::visited)
			foundUnvisited = true;
	}while(!foundUnvisited && !positionsStack.empty());

	//Cehck if we found the next unvisisted node.
	if (foundUnvisited)
	{
		//Visit the next node.
		currentPos = nextPos;
		//Mark the node at the current position as visited.
		graph[nextPos.Map2DTo1D(board.GetWidth())].state = NodeState::visited;
		//Check if the current position is the objective.
		if (board.GetCellType(currentPos) == CellType::objective)
		{
			//We found the objective.
			bFoundObjective = true;
			finalObjectivePath = CalculateFinalObjectivePath();
		}
		else
		{
			//Push all the valid adjacent cells to the stack.
			for (int i = 0; i < 4; ++i)
			{
				//Get the position of the adjacent cell.
				Vec2<int> adjacentPos = currentPos + Vec2{ directionX[i],directionY[i] };
				//Check if it's a valid cell.
				if (IsPositionValid(adjacentPos))
				{
					//Add it to the stack.
					positionsStack.push(adjacentPos);
					//Add the parent (this position) to the adjacent nodes so that we can trace back once we are done.
					Node& adjacentNode = graph[adjacentPos.Map2DTo1D(board.GetWidth())];
					adjacentNode.parent = currentPos;
					adjacentNode.state = NodeState::targeted;
				}
			}
		}
	}
}

void DFSRobot::DrawRobot() const
{
	board.DrawCell(currentPos,settings::robotColor);
}

void DFSRobot::DrawVisitedOutline() const
{
	for (int x = 0; x < board.GetWidth(); ++x)
	{
		for (int y = 0; y < board.GetHeight(); ++y)
		{
			if(graph[y * board.GetWidth() + x].state == NodeState::visited)
				board.DrawCellOutline({x,y},settings::visitedColor);
		}
	}
}

void DFSRobot::DrawTargetedOutline() const
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

void DFSRobot::DrawFinalObjectivePath() const
{
	assert(bFoundObjective);//If assertion triggers: the path to the objective hasn't been found yet.
	//Draw the path and enumeration
	int length = int(finalObjectivePath.size() - 1);
	for (auto& vec : finalObjectivePath)
	{
		board.DrawCellOutline(vec,settings::objectivePathColor);
		board.DrawCellNumber(vec,length--,settings::numbersColor);
	}

}

std::vector<Vec2<int>> DFSRobot::CalculateFinalObjectivePath() const
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

