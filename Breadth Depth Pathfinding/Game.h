#pragma once
#include <string>
#include <vector>
#include <memory>
#include "StateMachine.h"
#include "Board.h"
#include "Robot.h"

//A class that handles the game's screen, loop and logic.
class Game
{
public:
	Game(int width, int height, int fps, std::string title);
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	~Game() noexcept;
	bool GameShouldClose() const;
	void Tick();
private:
	void Update();
	void Draw();
private:
	Board board;
	std::unique_ptr<Robot> robot;
};