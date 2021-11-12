#include "RunningState.h"
#include "raylibCpp.h"

engine::RunningState::RunningState(std::shared_ptr<GameData> gameData)
	:
	gameData(std::move(gameData))
{
}

void engine::RunningState::HandleInput()
{
	if (IsKeyPressed(KEY_N))
	{
		gameData->robot->Next();
	}
}

void engine::RunningState::Update()
{
}

void engine::RunningState::Draw()
{
	ClearBackground(BLACK);
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
}