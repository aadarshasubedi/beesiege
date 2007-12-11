#ifndef FSMSTATE_H
#define FSMSTATE_H

#include "FSM.h"
#include "GameObj.h"

class FSMAIControl;
class HealthAttribute;
class GameManager;

class FSMState: public GameObj
{
public:

	// ctor / dtor
	FSMState(FSMAIControl* control, int type=FSM_STATE_NONE);
	virtual ~FSMState();

	// pure virtual functions
	
	// enters the state
	virtual void Enter() = 0;
	// exits the state
	virtual void Exit() = 0;            
	// updates the state
	virtual void Update(float fTime) = 0;
	// checks for transitions and returns the new state
	virtual FSMState* CheckTransitions(float fTime) = 0;
	
	// getters
	const int GetType() const 
	{
		return m_type;
	}

	FSMAIControl* GetAIControl() const
	{
		return m_control;
	}

protected:

	// the state's type
	int m_type;
	// the state's parent controller
	FSMAIControl* m_control;
	// the owner's health
	HealthAttribute* m_pOwnerHealth;

	// checks if the owner is dead
	// and sets it to non-active if it is
	bool IsOwnerDead();

	// pointer to the game manager
	GameManager* m_pGameManager;
};

NiSmartPointer(FSMState);

#endif