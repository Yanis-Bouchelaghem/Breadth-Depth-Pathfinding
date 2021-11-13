#include "FinishedState.h"
#include <sstream>

engine::FinishedState::FinishedState(std::shared_ptr<GameData> gameData)
	:
	gameData(gameData)
{
}

void engine::FinishedState::HandleInput()
{
}

void engine::FinishedState::Update(float dt)
{
}

void engine::FinishedState::Draw()
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
	//Result text
	if (gameData->robot->HasFoundObjective())
		raycpp::DrawText("Objective found!", Vec2<int>{400, 670}, settings::textFontSize, GREEN);
	else
		raycpp::DrawText("Objective not found", Vec2<int>{400, 670}, settings::textFontSize, RED);
}
