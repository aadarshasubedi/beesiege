#ifndef STATEQUEENSELECTGATHERERS_H
#define STATEQUEENSELECTGATHERERS_H

#include "FSMState.h"
#include <NiTPointerList.h>
#include "HoneyBee.h"

class Flower;

class StateQueenSelectGatherers: public FSMState
{
public:

	// ctor / dtor
	StateQueenSelectGatherers(FSMAIControl* control, int type=FSM_QUEEN_SELECTGATHERERS);
	~StateQueenSelectGatherers();
	
	// see base class
	void Enter();
	void Exit();
	void Update(float fTime);
	FSMState* CheckTransitions(float fTime);

	// setters / getters
	const NiTPointerList<HoneyBeePtr>& GetSelectedGatherers() const
	{
		return m_lSelectedGatherers;
	}
private:
	// adds more gatherers to the selection list
	void SelectMoreGatherers();
	// plays a sound when a bee is selected
	void PlaySelectionSound(HoneyBee* bee);
	// returns a soldier that is closest to a certain
	// position
	HoneyBeePtr FindGathererClosestTo(const NxVec3& position);
	
	
	// a list that contains te selected soldiers
	NiTPointerList<HoneyBeePtr> m_lSelectedGatherers;
	// the queen's target
	Flower* m_pTarget;
	// a timer that delays selection
	float m_fSelectionTimer;
	
};

NiSmartPointer(StateQueenSelectGatherers);

#endif