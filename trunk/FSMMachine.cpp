#include "FSM.h"
#include "FSMMachine.h"

FSMMachine::FSMMachine() : m_currentState(0),
						   m_goalState(0),
						   m_defaultState(0)
{
}

FSMMachine::~FSMMachine()
{
	Reset();
}

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
	FSMState* oldState =m_currentState;
	m_goalState = m_currentState->CheckTransitions(t);

	//change states if there was a transition
	if(m_goalState != oldState)
	{
		//if(TransitionState(m_goalState))
		{
			m_currentState->Exit();
			m_currentState = m_goalState;
			m_currentState->Enter();
		}
	}
	m_currentState->Update(t);
}

void FSMMachine::AddState(FSMState* state)
{
	if(state)
		m_states.push_back(state);

}

bool FSMMachine::TransitionState(FSMState* state)
{
	//todo
	return true;
}

FSMState* FSMMachine::GetState(int stateId)
{
	FSMState* state;
	int numStates = m_states.size();
	for(int i = 0; i< numStates; i++)
	{
		if(m_states.at(i)->m_type == stateId)
		{
			state = m_states.at(i);
			break;
		}
	}
	return state;
}

void FSMMachine::Reset()
{
	for (int i=0; i<m_states.size(); i++)
	{
		NiDelete m_states[i];
	}
	m_states.clear();
}


