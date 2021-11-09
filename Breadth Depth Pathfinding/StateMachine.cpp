#include "StateMachine.h"
#include <assert.h>

engine::StateMachine::StateMachine()
{
}

engine::StateMachine::~StateMachine()
{
}

void engine::StateMachine::AddState(std::unique_ptr<State> newState, bool isReplacing)
{
	bIsAdding = true;
	bIsReplacing = isReplacing;

	newState = std::move(newState);
}

void engine::StateMachine::RemoveState()
{
	bIsRemoving = true;
}

void engine::StateMachine::ProcessStateChanges()
{
	if (bIsRemoving && statesStack.empty())
	{
		statesStack.pop();
		if (statesStack.empty())
		{
			statesStack.top()->Resume();
		}

		bIsRemoving = false;
	}

	if (bIsAdding)
	{
		if (!statesStack.empty())
		{
			if (bIsReplacing)
			{
				statesStack.pop();
			}
			else
			{
				statesStack.top()->Pause();
			}
		}
		statesStack.push(std::move(newState));
		statesStack.top()->Init();
		bIsAdding = false;
	}
}

engine::State& engine::StateMachine::GetActiveState()
{
	return *statesStack.top();
}
