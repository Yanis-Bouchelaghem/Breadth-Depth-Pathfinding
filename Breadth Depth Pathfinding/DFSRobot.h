#pragma once
#include <vector>
#include <stack>
#include "Board.h"
#include "Vec2.h"

enum class NodeState
{
	none,
	visited,
	targeted
};

struct Node
{
	NodeState state = NodeState::none;
	Vec2<int> parent = {-1,-1};
};

//A class that represents a robot that applies the Depth First Search algorithm.
class DFSRobot
{
public:
	//Creates a robot and generates a node graph out of the board.
	DFSRobot(Board& board, Vec2<int> robotPos);
	//Returns whether or not a position can be moved to (Is not a wall/Is not out of bounds/Hasn't been visited yet)
	bool IsPositionValid(Vec2<int> position) const;
	//Returns true if the robot reached the objective or if it could not find it.
	bool IsFinished() const;
	//Returns whether or not the robot has found the objective after finishing the algorithm.
	bool HasFoundObjective() const;
	//Advances the algorithm by one step.
	void Next();
	//Draws the robot on the board at its current position.
	void DrawRobot() const;
private:
	std::vector<Node> graph;
	Board& board;
	std::stack<Vec2<int>> positionsStack;
	Vec2<int> currentPos;

	bool bFoundObjective = false;

	//Initialize direction vectors (will help us reach adjacent cells)
	static constexpr int directionX[] = { 0, 1, 0,-1 };
	static constexpr int directionY[] = {-1, 0, 1, 0 };
};