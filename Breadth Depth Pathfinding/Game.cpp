#include "Game.h"
#include <assert.h>
#include "raylibCpp.h"
#include "Settings.h"
#include "DFSRobot.h"
#include "BFSRobot.h"
#include "Vec2.h"
#include "RunningState.h"
#include "SetupState.h"

Game::Game(int width, int height, int fps, std::string title)
	:
	gameData(std::make_shared<GameData>())
{
	assert(!GetWindowHandle());	//If assertion triggers : Window is already opened
	SetTargetFPS(fps);
	InitWindow(width, height, title.c_str());
	gameData->board.SetCell(settings::initialObjectivePos,CellType::objective);
	gameData->stateMachine.AddState(std::make_unique<engine::SetupState>(gameData));
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
	gameData->stateMachine.ProcessStateChanges();

	gameData->stateMachine.GetActiveState().HandleInput();
	gameData->stateMachine.GetActiveState().Update(GetFrameTime());

}

void Game::Draw()
{
	ClearBackground(BLACK);
	gameData->stateMachine.GetActiveState().Draw();
}

GameData::GameData()
	:
	board(settings::widthHeight, settings::boardScreenPos, settings::cellRadius, settings::padding),
	robot(std::make_unique<BFSRobot>(board,settings::initialRobotPos))
{
}
