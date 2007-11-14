#ifndef STATEQUEENTARGETSOLDIERS_H
#define STATEQUEENTARGETSOLDIERS_H

#include "FSMState.h"
#include <NiTPointerList.h>
#include "Bee.h"

class Enemy;

class StateQueenSelectSoldiers: public FSMState
{
public:
	StateQueenSelectSoldiers(FSMAIControl* control, int type=FSM_QUEEN_SELECTSOLDIERS);
	~StateQueenSelectSoldiers();
	
	void Enter();
	void Exit();
	void Update(float fTime);
	FSMState* CheckTransitions(float fTime);

	void SetTarget(Enemy* target)
	{
		m_pTarget = target;
	}

	const NiTPointerList<BeePtr>& GetSelectedSoldiers() const
	{
		return m_lSelectedSoldiers;
	}
private:

	void SelectMoreSoldiers();

	NiTPointerList<BeePtr> m_lSelectedSoldiers;
	Enemy* m_pTarget;
	BeePtr FindSoldierClosestTo(const NxVec3& position);
	float m_fSelectionTimer;
};

NiSmartPointer(StateQueenSelectSoldiers);

#endif