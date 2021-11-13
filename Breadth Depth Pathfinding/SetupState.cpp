#include "SetupState.h"
#include <sstream>
#include <algorithm>
#include "Settings.h"
#include "Vec2.h"
#include "RunningState.h"

engine::SetupState::SetupState(std::shared_ptr<GameData> gameData)
	:
	gameData(std::move(gameData))
{
}

void engine::SetupState::HandleInput()
{
	///Detect when a user clicks on the board and change its content accordingly
	Vec2<int> mousePos{ GetMouseX(),GetMouseY() };
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
	{
		if (isPositionInsideBoard(mousePos))
		{
			//Calculate to which cell the mouse is clicking on
			Vec2<int> cellPos = (mousePos - settings::boardScreenPos) / (settings::cellRadius * 2);
			//If the clicked cell is occupied by the robot, do nothing
			if(gameData->robot->GetCurrentPosition() == cellPos)
				return;
			if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
			{
				//Move the bot to this cell if it's empty
				if(gameData->board.GetCellType(cellPos) == CellType::empty)
					gameData->robot->SetCurrentPosition(cellPos);
			}
			else
			{
				//Iterate to the next cell type
				switch (gameData->board.GetCellType(cellPos))
				{
					case CellType::empty:
						gameData->board.SetCell(cellPos, CellType::wall);
						break;
					case CellType::wall:
						gameData->board.SetCell(cellPos, CellType::objective);
						break;
					case CellType::objective:
						gameData->board.SetCell(cellPos, CellType::empty);
						break;
				}
			}
		}
	}

	//Adjust the timer
	if(IsKeyPressed(KEY_UP))
		gameData->timer = std::min(gameData->timer + 0.25f, 5.f);
	if(IsKeyPressed(KEY_DOWN))
		gameData->timer = std::max(gameData->timer - 0.25f, 0.25f);

	//Adjust the algorithm
	if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT))
		switch (gameData->algorithm)
		{
		case Algorithm::BreadthFirst:
			gameData->algorithm = Algorithm::DepthFirst;
			break;
		case Algorithm::DepthFirst:
			gameData->algorithm = Algorithm::BreadthFirst;
			break;
		}
	//Start the simulation once the players presses space
	if(IsKeyPressed(KEY_SPACE))
		gameData->stateMachine.AddState(std::make_unique<RunningState>(gameData),true);

}

void engine::SetupState::Update(float dt)
{

}

void engine::SetupState::Draw()
{
	gameData->board.Draw();
	gameData->robot->DrawRobot();

	//Draw the text
	std::stringstream timerText, algorithmText, cellChangeText;
	
	raycpp::DrawText("Press space to start", Vec2<int>{350, 680}, settings::textFontSize, WHITE);
	//Timer text
	timerText << "Timer : " << gameData->timer << " secs (Up/Down arrow key to adjust)";
	raycpp::DrawText(timerText.str(), Vec2<int>{280, 640}, int(settings::textFontSize / 1.5f), WHITE);
	//Algorithm text
	algorithmText << "Algorithm : ";
	if(gameData->algorithm == Algorithm::DepthFirst)
		algorithmText << "Depth First Search";
	else
		algorithmText << "Breadth First Search";
	algorithmText << " (Left/Right arrow key to change)";
	raycpp::DrawText(algorithmText.str(), Vec2<int>{200, 60}, int(settings::textFontSize/1.5f), GREEN);

	//Cell change text
	cellChangeText << "Left click to change cell / Right click to move robot";
	raycpp::DrawText(cellChangeText.str(), Vec2<int>{250, 20}, int(settings::textFontSize/1.5f), WHITE);
}

bool engine::SetupState::isPositionInsideBoard(Vec2<int> pos)
{
	using namespace settings;
	//Calculate if the position is inside of the board
	Vec2<int> boardBottomRight = boardScreenPos + widthHeight * cellRadius*2;
	return (pos.GetX() >= boardScreenPos.GetX() &&
		pos.GetX() < boardBottomRight.GetX() &&
		pos.GetY() >= boardScreenPos.GetY() &&
		pos.GetY() < boardBottomRight.GetY());
}
