#pragma once
#include <stack>
#include "Robot.h"
#include "Board.h"
#include "Vec2.h"

//A class that represents a robot that applies the Depth First Search algorithm.
class DFSRobot : public Robot
{
public:
	DFSRobot(Board& board, Vec2<int> robotPos);//Creates a robot and generates a node graph out of the board.
	void SetCurrentPosition(Vec2<int> newPos) override;//Sets the current position of the bot and puts it at the top of the container.
	bool IsFinished() const override;//Returns true if the robot reached the objective or if it could not find it.
	void Next() override;//Advances the algorithm by one step (basically contains the algorithm logic).
private:
	std::stack<Vec2<int>> positionsStack;
};