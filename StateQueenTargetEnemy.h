#ifndef STATEQUEENDEFAULT_H
#define STATEQUEENDEFAULT_H

#include "FSMState.h"
#include <NiTPointerList.h>

class Enemy;

class StateQueenTargetEnemy: public FSMState
{
public:
	StateQueenTargetEnemy(FSMAIControl* control, int type=FSM_QUEEN_TARGETENEMY) :
	  FSMState(control, type), m_pCurrentTarget(0)
	  {}
	
	void Enter();
	void Exit();
	void Update(float fTime);
	FSMState* CheckTransitions(float fTime);

private:

	void TargetNextEnemy();

	NiTListIterator m_itCurrentTargetPosition;
	Enemy* m_pCurrentTarget;
};

NiSmartPointer(StateQueenTargetEnemy);

#endif