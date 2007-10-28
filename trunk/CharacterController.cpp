#include "CharacterController.h"
#include "Agent.h"
#include <NxActor.h>
#include "AgentInfo.h"
#include "Behavior.h"
#include <NiViewMath.h>
#include <NiPhysX.h>
#include "ConfigurationManager.h"
#include "GameManager.h"
#define RAD 180.0f / 3.14159265f

//-------------------------------------------------------------------------
CharacterController::CharacterController(Agent* agent) : 
							           m_pAgent(agent),
									   m_spAgentInfo(NiNew AgentInfo),
									   m_spBehavior(0),									   
									   m_fcKv0(ConfigurationManager::Get()->characterController_springConstant),
									   m_fcDamp(ConfigurationManager::Get()->characterController_damping),									
									   m_fcPI(3.14159265f),
									   m_bTurnSpringsOff(false)


{
   
}
//-------------------------------------------------------------------------
CharacterController::~CharacterController()
{
	m_spAgentInfo = 0;
	m_spBehavior = 0;
}
//-------------------------------------------------------------------------
void CharacterController::Update(const NxVec3& target)
{
	Sense(target);
	UpdateForces();
	UpdatePhysX();
}
//-------------------------------------------------------------------------
void CharacterController::Sense(const NxVec3& target)
{
	m_spAgentInfo->m_vTarget      = target;
	m_spAgentInfo->m_vPos         = m_pAgent->GetActor()->getGlobalPosition();
	m_spAgentInfo->m_vVelocity    = m_pAgent->GetActor()->getLinearVelocity();
	m_spAgentInfo->m_vOrientation = m_spAgentInfo->m_vVelocity;
	m_spAgentInfo->m_vOrientation.normalize();

	m_spBehavior->Execute(m_spAgentInfo);
	
}
//-------------------------------------------------------------------------
void CharacterController::UpdateForces()
{
	m_spAgentInfo->m_vForce = - (-m_fcKv0 * (m_spAgentInfo->m_vDesiredVelocity - m_spAgentInfo->m_vVelocity)
							     + m_fcDamp *  m_spAgentInfo->m_vVelocity);
	NxVec3 heading = m_spAgentInfo->m_vForce;
	heading.normalize();
	if (m_spAgentInfo->m_vForce.magnitude() > m_spAgentInfo->m_fcMaxForce)
	{
		m_spAgentInfo->m_vForce = heading * m_spAgentInfo->m_fcMaxForce;
	}
	else if (m_spAgentInfo->m_vForce.magnitude() < -m_spAgentInfo->m_fcMaxForce)
	{
		m_spAgentInfo->m_vForce = heading * -m_spAgentInfo->m_fcMaxForce;
	}	
}
//-------------------------------------------------------------------------
void CharacterController::UpdatePhysX()
{
	
	if (!m_bTurnSpringsOff)
	{	
		m_pAgent->GetActor()->addForce(m_spAgentInfo->m_vForce, NX_FORCE);
	}
	
	
}
