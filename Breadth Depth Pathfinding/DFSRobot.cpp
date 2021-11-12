#include "DFSRobot.h"
#include <assert.h>

DFSRobot::DFSRobot(Board& board, Vec2<int> robotPos)
	:
	Robot(board, robotPos)
{
	positionsStack.push(robotPos);
}

bool DFSRobot::IsFinished() const
{
	return (positionsStack.empty() || bFoundObjective);
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