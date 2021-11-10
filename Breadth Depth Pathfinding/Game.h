#pragma once
#include <string>
#include <vector>
#include "StateMachine.h"
#include "Board.h"

//A class that handles the game's screen, loop and logic.
class Game
{
public:
	Game(int width, int height, Vec2<int> boardScreenPos, int fps, std::string title);
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
};