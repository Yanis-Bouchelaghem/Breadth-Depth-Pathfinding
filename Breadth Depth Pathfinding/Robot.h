#pragma once
#include <vector>
#include "Vec2.h"
//A base robot class that provides the same interface regardless of the algorithm
//Inherit from this and implement the functions to make a new robot
class Robot
{
public:
	virtual bool IsFinished() const = 0;//Returns true if the robot reached the objective or if it could not find it.
	virtual bool HasFoundObjective() const = 0;//Returns whether or not the robot has found the objective after finishing the algorithm.
	virtual void Next() = 0;//Advances the algorithm by one step.
	virtual void DrawRobot() const = 0;//Draws the robot on the board at its current position.
	virtual void DrawVisitedOutline() const = 0;//Outlines the visited cells.
	virtual void DrawTargetedOutline() const = 0;//Outlines the targeted cells.
	virtual void DrawFinalObjectivePath() const = 0;//Outlines the cells to take to reach the objective and enumerates them.
private:
	virtual bool IsPositionValid(Vec2<int> position) const = 0;//Returns whether or not a position can be moved to (Is not a wall/Is not out of bounds/Hasn't been visited yet/Isn't targeted yet)
	virtual std::vector<Vec2<int>> CalculateFinalObjectivePath() const = 0;//Traces back the path to the objective once the algorithm is finished.
};