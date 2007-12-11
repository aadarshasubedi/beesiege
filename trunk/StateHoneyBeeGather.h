#ifndef STATEHONEYBEEGATHER_H
#define STATEHONEYBEEGATHER_H

#include "FSMState.h"

class Flower;

class StateHoneyBeeGather: public FSMState
{
public:
	// ctor
	StateHoneyBeeGather(FSMAIControl* control, int type=FSM_GATHER_HONEY);
	
	// see base class
	void Enter();
	void Exit();
	void Update(float fTime);
	FSMState* CheckTransitions(float fTime);

private:

	// the bee's target
	Flower* m_pTarget;
	// amount of honey gathered per frame
	const float m_fcHoneyToken;
	// gathering timer
	const float m_fcGatherTime;
	float m_fGatherTimer;
	// gathering delay
	float m_fGatherDelayTimer;

	// gather honey
	void Gather();
	
};

NiSmartPointer(StateHoneyBeeGather);

#endif
