#ifndef STATEQUEENSELECTSOLDIERS_H
#define STATEQUEENSELECTSOLDIERS_H

#include "FSMState.h"
#include <NiTPointerList.h>
#include "Bee.h"

class Enemy;
class HealthAttribute;


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
	const NiTPointerList<BeePtr>& GetSelectedSoldiers() const
	{
		return m_lSelectedSoldiers;
	}
private:
	// adds more soldiers to the selection list
	void SelectMoreSoldiers();
	// plays a sound when a bee is selected
	void PlaySelectionSound(Bee* bee);
	// returns a soldier that is closest to a certain
	// position
	BeePtr FindSoldierClosestTo(const NxVec3& position);
	
	
	// a list that contains te selected soldiers
	NiTPointerList<BeePtr> m_lSelectedSoldiers;
	// the queen's target
	Enemy* m_pTarget;
	// a timer that delays selection
	float m_fSelectionTimer;
	// the target's health
	HealthAttribute* m_pTargetHealth;
	
};

NiSmartPointer(StateQueenSelectSoldiers);

#endif