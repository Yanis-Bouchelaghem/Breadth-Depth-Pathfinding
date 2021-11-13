#include "RunningState.h"
#include <sstream>
#include <memory>
#include "raylibCpp.h"
#include "BFSRobot.h"
#include "DFSRobot.h"
#include "FinishedState.h"
engine::RunningState::RunningState(std::shared_ptr<GameData> in_gameData)
	:
	gameData(std::move(in_gameData))
{
	//Save the position of the dummy robot
	Vec2<int> robotPos = gameData->robot->GetCurrentPosition();
	//Create a new robot depending on the algorithm
	switch (gameData->algorithm)
	{
	case Algorithm::BreadthFirst:
		gameData->robot = std::make_unique<BFSRobot>(gameData->board,robotPos);
		break;
	case Algorithm::DepthFirst:
		gameData->robot = std::make_unique<DFSRobot>(gameData->board, robotPos);
		break;
	}
}

void engine::RunningState::HandleInput()
{
	//Adjust the timer
	if (IsKeyPressed(KEY_UP))
		gameData->timer = std::min(gameData->timer + 0.25f, 5.f);
	if (IsKeyPressed(KEY_DOWN))
		gameData->timer = std::max(gameData->timer - 0.25f, 0.25f);
}

void engine::RunningState::Update(float dt)
{
	accumulator += dt;
	if (accumulator >= gameData->timer)
	{
		if (gameData->robot->IsFinished())
		{
			gameData->stateMachine.AddState(std::make_unique<FinishedState>(gameData), true);
		}
		else
		{
			//Advance the robot
			gameData->robot->Next();
			accumulator = 0.f;
			++gameData->moveCounter;
		}
	}
}

void engine::RunningState::Draw()
{
	gameData->board.Draw();
	gameData->robot->DrawRobot();
	gameData->robot->DrawVisitedOutline();
	gameData->robot->DrawTargetedOutline();
	if (gameData->robot->IsFinished())
	{
		if (gameData->robot->HasFoundObjective())
		{
			gameData->robot->DrawFinalObjectivePath();
		}
	}

	//Draw the text
	std::stringstream TimerText, moveCountText, algorithmText;
	//Timer text
	TimerText << "Timer : " << gameData->timer << " secs (Up/Down arrow key to adjust)";
	raycpp::DrawText(TimerText.str(), Vec2<int>{280, 640}, int(settings::textFontSize / 1.5f), WHITE);
	//Move count text
	moveCountText << "Number of moves : " << gameData->moveCounter;
	raycpp::DrawText(moveCountText.str(), Vec2<int>{380, 10}, settings::textFontSize, GREEN);
	//Algorithm text
	algorithmText << "Algorithm : ";
	if (gameData->algorithm == Algorithm::DepthFirst)
		algorithmText << "Depth First Search";
	else
		algorithmText << "Breadth First Search";
	raycpp::DrawText(algorithmText.str(), Vec2<int>{380, 60}, int(settings::textFontSize / 1.5f), GREEN);
}