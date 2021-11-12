#pragma once
#include <vector>
#include "Vec2.h"
#include "Board.h"

enum class NodeState
{
	none,
	visited,
	targeted
};

struct Node
{
	NodeState state = NodeState::none;
	Vec2<int> parent = { -1,-1 };
};

//A base robot class that provides the same interface regardless of the algorithm
//Inherit from this and implement the pure virtual functions to make a new robot
class Robot
{
public:
	Robot(Board& board, Vec2<int> robotPos);
	
	virtual bool HasFoundObjective() const;//Returns whether or not the robot has found the objective after finishing the algorithm.
	virtual void DrawRobot();//Draws the robot on the board at its current position.
	virtual void DrawVisitedOutline();//Outlines the visited cells.
	virtual void DrawTargetedOutline();//Outlines the targeted cells.
	virtual void DrawFinalObjectivePath();//Outlines the cells to take to reach the objective and enumerates them.

	virtual void Next() = 0;//Advances the algorithm by one step (basically contains the algorithm logic).
	virtual bool IsFinished() const = 0;//Returns true if the robot reached the objective or if it could not find it.
protected:
	virtual bool IsPositionValid(Vec2<int> position) const;//Returns whether or not a position can be moved to (Is not a wall/Is not out of bounds/Hasn't been visited yet/Isn't targeted yet)
	virtual std::vector<Vec2<int>> CalculateFinalObjectivePath();//Traces back the path to the objective once the algorithm is finished.
protected:
	std::vector<Node> graph;
	Board& board;
	Vec2<int> currentPos;

	//A vector to hold the path towards the objective once the algorithm is finished
	std::vector<Vec2<int>> finalObjectivePath;
	bool bFoundObjective = false;
	//Initialize direction vectors (will help us reach adjacent cells)
	static constexpr int directionX[] = { 0, 1, 0,-1 };
	static constexpr int directionY[] = { -1, 0, 1, 0 };
};