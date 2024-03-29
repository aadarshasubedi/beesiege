#ifndef STATEQUEENDEFAULT_H
#define STATEQUEENDEFAULT_H

#include "FSMState.h"
#include <NiTPointerList.h>

class Enemy;
class HealthAttribute;

class StateQueenTargetEnemy: public FSMState
{
public:
	// ctor
	StateQueenTargetEnemy(FSMAIControl* control, int type=FSM_QUEEN_TARGETENEMY) :
	  FSMState(control, type), m_pCurrentTarget(0), m_pTargetHealth(0)
	  {}
	
	// see base class
	void Enter();
	void Exit();
	void Update(float fTime);
	FSMState* CheckTransitions(float fTime);

private:
	// targets next enemy
	void TargetNextEnemy();
	// deselects current target
	void DeselectCurrent();
	// the iterator that points to the current target
	// in the enemy list. The enemy list comes from the 
	// GameManager
	NiTListIterator m_itCurrentTargetPosition;
	// the queen's current target
	Enemy* m_pCurrentTarget;
	// the target's health
	HealthAttribute* m_pTargetHealth;
};

NiSmartPointer(StateQueenTargetEnemy);

#endif