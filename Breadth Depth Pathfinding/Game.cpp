#include "Game.h"
#include <assert.h>
#include "raylibCpp.h"
#include "Settings.h"
Game::Game(int width, int height, int fps, std::string title)
	:
	board(settings::widthHeight, settings::boardScreenPos, settings::cellRadius, settings::padding),
	dfsRobot(board,{3,3})
{
	assert(!GetWindowHandle());	//If assertion triggers : Window is already opened
	SetTargetFPS(fps);
	InitWindow(width, height, title.c_str());
	board.SetCell({1,1},CellType::objective);
	board.SetCell({2,8},CellType::wall);
	board.SetCell({5,3},CellType::wall);
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
		dfsRobot.Next();
	}
}

void Game::Draw()
{
	ClearBackground(BLACK);
	board.Draw();
	dfsRobot.DrawRobot();
}



