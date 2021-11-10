#include "StateMachine.h"
#include <assert.h>

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
	if (bIsRemoving)
	{
		//Removes the active state and resumes the previous one if it exists.
		assert(!statesStack.empty()); //If assertion triggers : There are no states to remove
		statesStack.pop();
		if (!statesStack.empty())
		{
			statesStack.top()->Resume();
		}

		bIsRemoving = false;
	}

	if (bIsAdding)
	{
		//Either pauses or removes the previous state, then adds the new one.
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
