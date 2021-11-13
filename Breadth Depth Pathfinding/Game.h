#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Board.h"
#include "Robot.h"
#include "StateMachine.h"
#include "Settings.h"

enum struct Algorithm
{
	DepthFirst,
	BreadthFirst
};

//Contains all of the game's data
struct GameData
{
	GameData(); //Initializes the game's data
	Board board;
	std::unique_ptr<Robot> robot;
	engine::StateMachine stateMachine;
	float timer = settings::initialTimer;
	Algorithm algorithm = Algorithm::DepthFirst;
};


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
	std::shared_ptr<GameData> gameData;
};