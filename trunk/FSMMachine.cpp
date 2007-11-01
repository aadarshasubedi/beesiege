#include "FSM.h"
#include "FSMMachine.h"

void FSMMachine::UpdateMachine(int t)
{
	if(m_states.size() == 0)
		return;

	if(!m_currentState)
		m_currentState = m_defaultState;
	if(!m_currentState)
		return;

	//update current state and check for transition
	int oldStateId = m_currentState->m_type;
	m_goalId = m_currentState->CheckTransitions(t);

	//change states if there was a transition
	if(m_goalId != oldStateId)
	{
		if(TransitionState(m_goalId))
		{
			m_currentState->Exit();
			m_currentState = m_goalState;
			m_currentState->Enter();
		}
	}
	m_currentState->Update(t);
}

bool FSMMachine::TransitionState(int goal)
{
	//todo
	return true;
}

