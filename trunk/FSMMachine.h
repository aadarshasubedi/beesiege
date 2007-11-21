#ifndef FSMMACHINE_H
#define FSMMACHINE_H

#include "FSM.h"
#include "GameObj.h"
#include <NiTMap.h>
#include "FSMState.h"

class FSMMachine: public GameObj
{
public:

	// ctor / dtor
	FSMMachine();
	virtual ~FSMMachine();
	// updates the FSM
	virtual void UpdateMachine(float fTime);
	// adds a state with a given type to the FSM
	void AddState(FSMStatePtr state, FSM_STATES type);
	
	// resets the FSM
	void Reset();
	
	// gets a state of the given type from the
	// FSM's hash table
	FSMStatePtr GetState(FSM_STATES type);

	// getters / setters
	void SetDefaultState (FSMStatePtr state)
	{
		m_spDefaultState = state;
	}

	void SetCurrentState (FSMStatePtr state)
	{
		m_spCurrentState = state;
	}

	FSMStatePtr GetDefaultState() const
	{
		return m_spDefaultState;
	}

	FSMStatePtr GetCurrentState() const
	{
		return m_spCurrentState;
	}

	FSMStatePtr GetGoalState() const
	{
		return m_spGoalState;
	}

protected:

	// hash table that contains the FSM's states
	NiTMap<FSM_STATES, FSMStatePtr> m_tStates;

	// current, default and goal states
	FSMStatePtr m_spCurrentState;
	FSMStatePtr m_spDefaultState;
	FSMStatePtr m_spGoalState;
};

NiSmartPointer(FSMMachine);

#endif
	
	
