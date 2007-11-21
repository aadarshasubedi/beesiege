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

	float kx = 1.0f;
	float ky = 1.0f;
	float kz = 1.0f;

	NxVec3 Tx(0.0f, 0.0f, 0.0f);
	NxVec3 Ty(0.0f, 0.0f, 0.0f);
	NxVec3 Tz(0.0f, 0.0f, 0.0f);

	NxVec3 x(m_pAgent->GetActor()->getGlobalOrientation().getColumn(0));
	NxVec3 y(m_pAgent->GetActor()->getGlobalOrientation().getColumn(1));
	NxVec3 z(m_pAgent->GetActor()->getGlobalOrientation().getColumn(2));

	NxVec3 xd = m_spAgentInfo->m_vDesiredVelocity / m_spAgentInfo->m_vDesiredVelocity.magnitude();
	NxVec3 yd(0.0, 1.0, 0.0);
	NxVec3 zd = xd.cross(yd);
	zd.normalize();

	Tx = kx * x.cross(xd);
	Ty = ky * y.cross(yd);
	Tz = kz * z.cross(zd);

	m_spAgentInfo->m_vTorque = Tx + Ty + Tz;
}
//-------------------------------------------------------------------------
/** 
 * Adds the force to the object's PhysX actor
 * 
 */
void CharacterController::UpdatePhysX()
{
	
	if (!m_bTurnSpringsOff)
	{	// if springs on then add the force that we found
		m_pAgent->GetActor()->addForce(m_spAgentInfo->m_vForce);
		m_pAgent->GetActor()->addTorque(m_spAgentInfo->m_vTorque);
	}
	// TO_BE_REMOVED
	else
	{
		// if springs off then add a fake gravity
		NxVec3 gravity(0.0, -90.8f, 0.0f);
		m_pAgent->GetActor()->addForce(gravity, NX_ACCELERATION);
	}
	
	
}
