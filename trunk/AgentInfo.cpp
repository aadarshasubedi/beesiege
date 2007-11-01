/**
 * Information about an agent that the CharacterController needs
 */
#include "AgentInfo.h"
#include "ConfigurationManager.h"

//------------------------------------------------------------------------------------------- 
/** 
 * Ctor
 * 
 */
AgentInfo::AgentInfo() :    m_fcMass(1.0f),
							m_fcInertia(1.0f),
							m_vForce(0.0, 0.0, 0.0),
							m_vTorque(0.0, 0.0, 0.0),
							m_vVelocity(0.0, 0.0, 0.0),
							m_vAngVelocity(0.0, 0.0, 0.0),
							m_vDesiredVelocity(0.0, 0.0, 0.0),
							m_vPos(0.0, 0.0, 0.0),
							m_vTarget(0.0, 0.0, 0.0),
							m_vOrientation(0.0, 0.0, 0.0),
							m_vDesiredOrientation(0.0, 0.0, 0.0),
							m_fcMaxForce(ConfigurationManager::Get()->agent_maxForce),
							m_fcMaxTorque(ConfigurationManager::Get()->agent_maxTorque),
							m_fcMaxVelocity(ConfigurationManager::Get()->agent_maxVelocity),
							m_fcMaxAngVel(ConfigurationManager::Get()->agent_maxAngVel)
							
							
{
}
//------------------------------------------------------------------------------------------- 
/** 
 * Dtor
 * 
 */
AgentInfo::~AgentInfo()
{
}