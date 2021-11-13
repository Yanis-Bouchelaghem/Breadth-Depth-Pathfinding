#pragma once
#include <memory>
#include <stack>
#include "State.h"
namespace engine
{
	//A state machine that manages the game states.
	class StateMachine
	{
	public:
		StateMachine() = default;

		//Marks a new state for addition.
		void AddState(std::unique_ptr<State> in_newState, bool isReplacing = false);
		//Marks the active for removal.
		void RemoveState();
		//processes the states marked for addition or removal.
		void ProcessStateChanges();

		State& GetActiveState();
	private:
		std::stack<std::unique_ptr<State>> statesStack;
		std::unique_ptr<class State> newState;

		bool bIsRemoving = false;
		bool bIsAdding = false;
		bool bIsReplacing = false;
	};
}