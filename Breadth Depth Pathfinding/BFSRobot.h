#pragma once
#include "Robot.h"
#include "Board.h"
#include <queue>

//A class that represents a robot that applies the Breadth First Search algorithm.
class BFSRobot : public Robot
{
public:
	BFSRobot(Board& board, Vec2<int> robotPos);
	bool IsFinished() const override;//Returns true if the robot reached the objective or if it could not find it.
	void Next() override;//Advances the algorithm by one step (basically contains the algorithm logic).
private:
	std::queue<Vec2<int>> positionsQueue;
};