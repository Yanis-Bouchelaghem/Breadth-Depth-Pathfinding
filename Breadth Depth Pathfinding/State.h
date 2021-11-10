#pragma once

namespace engine
{
	//A base class to represent a particular game state.
	//Inherit from this and implement the functions to handle a state.
	class State
	{
	public:
		virtual void Init() = 0;

		virtual void HandleInput() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;

		virtual void Pause() {};
		virtual void Resume() {};
	};
}