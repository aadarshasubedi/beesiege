/**
*	A Finite State Machine
*/
#include "FSMMachine.h"

//------------------------------------------------------
/**
* Ctor
*/
FSMMachine::FSMMachine() : m_spCurrentState(0),
						   m_spGoalState(0),
						   m_spDefaultState(0)
{
}
//------------------------------------------------------
/**
* Dtor
*/
FSMMachine::~FSMMachine()
{
	Reset();
}
//------------------------------------------------------
/**
* Checks the current state for transitions and goes to 
* a new state if necessary
* @param delta time
*/
void FSMMachine::UpdateMachine(float fTime)
{
	if (m_tStates.IsEmpty()) return;

	if(!m_spCurrentState)
	{
		if (!m_spDefaultState)
			return;

		m_spCurrentState = m_spDefaultState;
		m_spCurrentState->Enter();
	}
	

	//update current state and check for transition
	int oldStateId = m_spCurrentState->GetType();
	FSMState* oldState = m_spCurrentState;
	m_spGoalState = m_spCurrentState->CheckTransitions(fTime);

	//change states if there was a transition
	if(m_spGoalState != oldState)
	{
		{
			m_spCurrentState->Exit();
			m_spCurrentState = m_spGoalState;
			if (m_spCurrentState )
				m_spCurrentState->Enter();
			else
				return;
		}
	}
	m_spCurrentState->Update(fTime);
}
//------------------------------------------------------
/**
* Adds a new FSM state to the table
* @param State type and State
*/
void FSMMachine::AddState(FSMStatePtr state, FSM_STATES type)
{
	if(state)
	{
		m_tStates.SetAt(type, state);
	}

}
//------------------------------------------------------
/**
* Gets the state associated with a spcific type
* @param State type 
*/
FSMStatePtr FSMMachine::GetState(FSM_STATES stateId)
{
	if (m_tStates.IsEmpty()) return 0;
	
	FSMStatePtr state = 0;
	m_tStates.GetAt(stateId, state);
	return state;
}
//------------------------------------------------------
/**
* Resets the FSM 
*/
void FSMMachine::Reset()
{
	m_spCurrentState = 0;
	m_spDefaultState = 0;
	m_spGoalState = 0;
	m_tStates.RemoveAll();
}


