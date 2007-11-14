#ifndef FSMMACHINE_H
#define FSMMACHINE_H

#include "FSM.h"
#include "GameObj.h"
#include <NiTMap.h>
#include "FSMState.h"

class FSMMachine: public GameObj
{
public:

	FSMMachine();
	virtual ~FSMMachine();

	virtual void UpdateMachine(float fTime);
	void AddState(FSMStatePtr state, FSM_STATES type);
	virtual void SetDefaultState(FSMStatePtr state)
	{ 
		m_spDefaultState = state;
	}
	virtual void SetGoalID(FSMStatePtr state)
	{
		m_spGoalState = state;
	}
	
	void Reset();
	
	FSMStatePtr GetState(FSM_STATES type);
	FSMStatePtr m_spCurrentState;
	FSMStatePtr m_spDefaultState;
	FSMStatePtr m_spGoalState;

protected:

	NiTMap<FSM_STATES, FSMStatePtr> m_tStates;
};

NiSmartPointer(FSMMachine);

#endif
	
	
