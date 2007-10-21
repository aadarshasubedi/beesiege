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
	// angle
	float m_fAngle;
	// desired velocity
	NxVec3 m_vDesiredVelocity;
	// desired angle
	float m_fThetaDesired;
	// current position
	NxVec3 m_vPos;
	// target position
	NxVec3 m_vTarget;
	// orientation
	NxVec3 m_vOrientation;
	// desired orientation
	NxVec3 m_vDesiredOrientation;
	// max force
	const float m_fcMaxForce;
	// max torque
	const float m_fcMaxTorque;
	// max velocity
	const float m_fcMaxVelocity;
	// max angular velocity
	const float m_fcMaxAngVel;

	// secondary
	float m_fVelocity;
	float m_fVelocityDesired;
	float m_fYaw;
	float m_fYawDesired;
	float m_fPitch;
	float m_fPitchDesired;
	float m_fForce;
	float m_fTorque;
	float m_fAngVelocityYaw;
	float m_fAngVelocityPitch;

};

NiSmartPointer(AgentInfo);
#endif