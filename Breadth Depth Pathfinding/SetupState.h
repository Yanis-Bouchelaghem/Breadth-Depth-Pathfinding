#pragma once
#include "State.h"
#include "Game.h"

namespace engine
{
	class SetupState : public State
	{
	public:
		SetupState(std::shared_ptr<GameData> gameData);
		void HandleInput() override;
		void Update(float dt) override;
		void Draw() override;
	private:
		bool isPositionInsideBoard(Vec2<int> pos);
	private:
		std::shared_ptr<GameData> gameData;
	};
}