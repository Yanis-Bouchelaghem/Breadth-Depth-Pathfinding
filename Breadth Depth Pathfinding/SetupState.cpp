#include "SetupState.h"
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

	//Start the simulation once the players presses space
	if(IsKeyPressed(KEY_SPACE))
		gameData->stateMachine.AddState(std::make_unique<RunningState>(gameData),true);
}

void engine::SetupState::Update()
{

}

void engine::SetupState::Draw()
{
	gameData->board.Draw();
	gameData->robot->DrawRobot();
	raycpp::DrawText("Press space to start.",Vec2<int>{350,700},settings::textFontSize,WHITE);
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
