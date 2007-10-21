#include "AgentInfo.h"

AgentInfo::AgentInfo() :    m_fcMass(1.0f),
							m_fcInertia(1.0f),
							m_vForce(0.0, 0.0, 0.0),
							m_vTorque(0.0, 0.0, 0.0),
							m_vVelocity(0.0, 0.0, 0.0),
							m_vAngVelocity(0.0, 0.0, 0.0),
							m_fAngle(0.0f),
							m_vDesiredVelocity(0.0, 0.0, 0.0),
							m_fThetaDesired(0.0f),
							m_vPos(0.0, 0.0, 0.0),
							m_vTarget(0.0, 0.0, 0.0),
							m_vOrientation(0.0, 0.0, 0.0),
							m_vDesiredOrientation(1.0, 0.0, 0.0),
							m_fcMaxForce(10.0f),
						    m_fcMaxTorque(40.0f),
						    m_fcMaxVelocity(300.0f),
						    m_fcMaxAngVel(10.0f),
							m_fYaw(0.0f),
							m_fVelocity(0.0f)
							
{
}

AgentInfo::~AgentInfo()
{
}