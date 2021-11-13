#pragma once

#include "State.h"
#include "Game.h"

namespace engine
{
	class FinishedState : public State
	{
	public:
		FinishedState(std::shared_ptr<GameData> gameData);
		void HandleInput() override;
		void Update(float dt) override;
		void Draw() override;
	private:
		std::shared_ptr<GameData> gameData;
	};
}