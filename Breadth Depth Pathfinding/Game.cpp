#include "Game.h"
#include <assert.h>
#include "raylibCpp.h"
#include "Settings.h"
#include "DFSRobot.h"
#include "Vec2.h"

Game::Game(int width, int height, int fps, std::string title)
	:
	board(settings::widthHeight, settings::boardScreenPos, settings::cellRadius, settings::padding),
	robot(std::make_unique<DFSRobot>(board,Vec2{4,3}))
{
	assert(!GetWindowHandle());	//If assertion triggers : Window is already opened
	SetTargetFPS(fps);
	InitWindow(width, height, title.c_str());
	board.SetCell({10,2},CellType::objective);
	board.SetCell({2,8},CellType::wall);
	board.SetCell({5,3},CellType::wall);
	board.SetCell({6,3},CellType::wall);
	board.SetCell({7,3},CellType::wall);
	board.SetCell({8,3},CellType::wall);
	board.SetCell({9,3},CellType::wall);
	board.SetCell({10,3},CellType::wall);
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
		robot->Next();
	}
}

void Game::Draw()
{
	ClearBackground(BLACK);
	board.Draw();
	robot->DrawRobot();
	robot->DrawVisitedOutline();
	robot->DrawTargetedOutline();
	if (robot->IsFinished())
	{	
		if (robot->HasFoundObjective())
		{
			robot->DrawFinalObjectivePath();
		}
	}
}



