#ifndef AGENTINFO_H_
#define AGENTINFO_H_

#include "GameObj.h"
#include <NxVec3.h>


class AgentInfo : public GameObj
{
public:

	AgentInfo();
	~AgentInfo();

	// Mass 
	const float m_fcMass;
	// Inertia
	const float m_fcInertia;
	// force
	NxVec3 m_vForce;
	// torque
	NxVec3 m_vTorque;
	// velocity
	NxVec3 m_vVelocity;
	// angular velocity
	NxVec3 m_vAngVelocity;
	// desired velocity
	NxVec3 m_vDesiredVelocity;
	// current position
	NxVec3 m_vPos;
	// target position
	NxVec3 m_vTarget;
	// orientation
	NxVec3 m_vOrientation;
	// deired orientation
	NxVec3 m_vDesiredOrientation;
	// max force
	const float m_fcMaxForce;
	// max torque
	const float m_fcMaxTorque;
	// max velocity
	const float m_fcMaxVelocity;
	// max angular velocity
	const float m_fcMaxAngVel;
	// max allowed height
	const float m_fcMaxHeight;


};

NiSmartPointer(AgentInfo);
#endif