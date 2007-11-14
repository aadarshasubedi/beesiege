#ifndef FSMSTATE_H
#define FSMSTATE_H

#include "FSM.h"
#include "GameObj.h"

class FSMAIControl;

class FSMState: public GameObj
{
public:

	FSMState(FSMAIControl* control, int type=FSM_STATE_NONE);
	virtual ~FSMState();
	virtual void Enter() = 0;
	virtual void Exit() = 0;            
	virtual void Update(float fTime) = 0;
	virtual FSMState* CheckTransitions(float fTime) = 0;

	const int GetType() const 
	{
		return m_type;
	}

	FSMAIControl* GetAIControl() const
	{
		return m_control;
	}

protected:
	int m_type;
	FSMAIControl* m_control;
};

NiSmartPointer(FSMState);

#endif