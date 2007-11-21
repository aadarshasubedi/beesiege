#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "GameObj.h"
#include "AgentInfo.h"
#include "Behavior.h"
#include <NxVec3.h>

class Agent;
NiSmartPointer(Agent);

class CharacterController : public GameObj
{
public:
	
	// ctor
	CharacterController(Agent* agent);
	// dtor
	virtual ~CharacterController();
	// updates the controller
	void Update(const NxVec3& target);

	// getters / setters
	inline void       SetBehavior          (BehaviorPtr b) { m_spBehavior = 0; m_spBehavior = b; }
	inline void       ToggleSpringDynamics (bool off)    { m_bTurnSpringsOff = off; }
	inline AgentInfoPtr GetAgentInfo() const         { return m_spAgentInfo; }

protected:

	// collects information needed for the simulation
	void Sense(const NxVec3& target);
	// calculates the force that will move the agent
	void UpdateForces();
	// passes forces to PhysX
	void UpdatePhysX();

	// the agent that the controller controls
	Agent*      m_pAgent;
	// Agent position, orientation etc.
	AgentInfoPtr m_spAgentInfo;
	// current behavior
	BehaviorPtr  m_spBehavior;
	// velocity control
	const float m_fcKv0;
	// damping constant
	const float m_fcDamp;
	// PI
	const float m_fcPI;
	// turn spring dynamics off
	bool   m_bTurnSpringsOff;

	// clamps an angle in a range
	void Clamp(float& degree, float minV, float maxV){
	float delta = maxV - minV;
	if (degree > maxV){
		while (degree > maxV){
			degree -= delta;
		}
	}
	else{
		while (degree < minV){
			degree += delta;
		}
	}
}

	// trancates a value in a range
	void Truncate(float& value, float minV, float maxV){
		if (value < minV)
			value = minV;
		else
			if (value > maxV)
				value = maxV;
	}

	// returns the difference between two angles
	float AngleDiff(float source, float target)
	{
		float dangle = target - source;
		if (fabs(dangle) > m_fcPI){
			if (dangle > 0.0f)
				dangle = dangle - m_fcPI * 2.0f;
			else
				dangle = m_fcPI * 2.0f + dangle;
		}
		return dangle;
	}

};

NiSmartPointer(CharacterController);
#endif


