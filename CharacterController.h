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
	
	CharacterController(Agent* agent);
	virtual ~CharacterController();

	void Update(const NxVec3& target);
	inline void       SetBehavior          (BehaviorPtr b) { m_spBehavior = 0; m_spBehavior = b; }
	inline void       ToggleSpringDynamics (bool off)    { m_bTurnSpringsOff = off; }
	inline AgentInfoPtr GetAgentInfo() const         { return m_spAgentInfo; }

protected:

	void Sense(const NxVec3& target);
	void UpdateForces();
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


	inline void Clamp(float& degree, float minV, float maxV){
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


inline void Truncate(float& value, float minV, float maxV){
	if (value < minV)
		value = minV;
	else
		if (value > maxV)
			value = maxV;
}

inline float AngleDiff(float source, float target)
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


