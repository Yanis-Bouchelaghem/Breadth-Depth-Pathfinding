#include "Game.h"
#include <assert.h>
#include "raylibCpp.h"
#include "Settings.h"
#include "DFSRobot.h"
#include "BFSRobot.h"
#include "Vec2.h"

Game::Game(int width, int height, int fps, std::string title)
	:
	gameData(std::make_shared<GameData>())
{
	assert(!GetWindowHandle());	//If assertion triggers : Window is already opened
	SetTargetFPS(fps);
	InitWindow(width, height, title.c_str());
	gameData->board.SetCell({10,2},CellType::objective);
	gameData->board.SetCell({2,8},CellType::wall);
	gameData->board.SetCell({5,3},CellType::wall);
	gameData->board.SetCell({6,3},CellType::wall);
	gameData->board.SetCell({7,3},CellType::wall);
	gameData->board.SetCell({8,3},CellType::wall);
	gameData->board.SetCell({9,3},CellType::wall);
	gameData->board.SetCell({10,3},CellType::wall);
}

Game::~Game() noexcept
{
	assert(GetWindowHandle()); //If assertion triggers : Window is already closed
	CloseWindow();
}

bool Game::GameShouldClose() const
{
	return WindowShouldClose();
}

void Game::Tick()
{
	BeginDrawing();
	Update();
	Draw();
	EndDrawing();
}

void Game::Update()
{
	if (IsKeyPressed(KEY_N))
	{
		gameData->robot->Next();
	}
}

void Game::Draw()
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

GameData::GameData()
	:
	board(settings::widthHeight, settings::boardScreenPos, settings::cellRadius, settings::padding),
	robot(std::make_unique<BFSRobot>(board,Vec2{4,3}))
{
}
