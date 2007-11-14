/**
 * A CharacterController takes a desired velocity from a 
 * behavior, and computes a force that is used to bring the 
 * PhysX system of the object to a steady state, where 
 * desiredVelocity = currentVelocity. 
 */
#include "CharacterController.h"
#include "Agent.h"
#include "AgentInfo.h"
#include "Behavior.h"
#include "ConfigurationManager.h"
#include "GameManager.h"
#include <NxActor.h>
#include <NiViewMath.h>
#include <NiPhysX.h>

// degrees to rads
#define RAD 180.0f / 3.14159265f

//------------------------------------------------------------------------- 
/** 
 * Ctor
 * 
 * @param agent
 */
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
/** 
 * Dtor
 * 
 */
CharacterController::~CharacterController()
{
	m_spAgentInfo = 0;
	m_spBehavior = 0;
}
//------------------------------------------------------------------------- 
/** 
 * Senses the environment to get a desired velocity, generates a 
 * force and updates the object's PhysX actor 
 * 
 * @param target
 */
void CharacterController::Update(const NxVec3& target)
{
	if (!m_bTurnSpringsOff)
	{
		Sense(target);
		UpdateForces();
	}

	UpdatePhysX();
}
//------------------------------------------------------------------------- 
/** 
 * Executes the current behavior to get a desired velocity
 * 
 * @param target
 */
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
/** 
 * Generates a force based on a current and a desired velocity
 * 
 */
void CharacterController::UpdateForces()
{
	// generate force
	m_spAgentInfo->m_vForce = - (-m_fcKv0 * (m_spAgentInfo->m_vDesiredVelocity - m_spAgentInfo->m_vVelocity)
							     + m_fcDamp *  m_spAgentInfo->m_vVelocity);
	// constrain force
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
/** 
 * Adds the force to the object's PhysX actor
 * 
 */
void CharacterController::UpdatePhysX()
{
	
	if (!m_bTurnSpringsOff)
	{	
		m_pAgent->GetActor()->addForce(m_spAgentInfo->m_vForce, NX_FORCE);
	}
	else
	{
		NxVec3 gravity(0.0, -90.8f, 0.0f);
		m_pAgent->GetActor()->addForce(gravity, NX_ACCELERATION);
	}
	
	
}
