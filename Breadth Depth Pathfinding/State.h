#pragma once
#include <memory>

namespace engine
{
	//A base class to represent a particular game state.
	//Inherit from this and implement the functions to handle a state.
	class State
	{
	public:
		virtual void HandleInput() = 0;
		virtual void Update(float dt) = 0;
		virtual void Draw() = 0;

		virtual void Init() {};
		virtual void Pause() {};
		virtual void Resume() {};

	};
}