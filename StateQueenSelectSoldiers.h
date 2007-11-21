#ifndef STATEQUEENTARGETSOLDIERS_H
#define STATEQUEENTARGETSOLDIERS_H

#include "FSMState.h"
#include <NiTPointerList.h>
#include "Bee.h"

class Enemy;

class StateQueenSelectSoldiers: public FSMState
{
public:

	// ctor / dtor
	StateQueenSelectSoldiers(FSMAIControl* control, int type=FSM_QUEEN_SELECTSOLDIERS);
	~StateQueenSelectSoldiers();
	
	// see base class
	void Enter();
	void Exit();
	void Update(float fTime);
	FSMState* CheckTransitions(float fTime);

	// setters / getters
	void SetTarget(Enemy* target)
	{
		m_pTarget = target;
	}

	const NiTPointerList<BeePtr>& GetSelectedSoldiers() const
	{
		return m_lSelectedSoldiers;
	}
private:
	// adds more soldiers to the sellection list
	void SelectMoreSoldiers();
	// returns a soldier that is closest to a certain
	// position
	BeePtr FindSoldierClosestTo(const NxVec3& position);
	// a list that contains te selected soldiers
	NiTPointerList<BeePtr> m_lSelectedSoldiers;
	// the queen's target
	Enemy* m_pTarget;
	// a timer that delays selection
	float m_fSelectionTimer;
};

NiSmartPointer(StateQueenSelectSoldiers);

#endif