#pragma once
#include <memory>
#include <stack>
#include "State.h"
namespace engine
{
	class StateMachine
	{
	public:
		StateMachine();
		~StateMachine();

		void AddState(std::unique_ptr<State> newState, bool isReplacing = false);
		void RemoveState();

		void ProcessStateChanges();

		State& GetActiveState();

	private:
		std::stack<std::unique_ptr<State>> statesStack;
		std::unique_ptr<State> newState;

		bool bIsRemoving = false;
		bool bIsAdding = false;
		bool bIsReplacing = false;
	};
}