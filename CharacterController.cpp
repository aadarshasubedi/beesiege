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
									   m_fcKv0(ConfigurationManager::Get()->characterController_springConstantForce),
									   m_fcDamp0(ConfigurationManager::Get()->characterController_dampingForce),									
									   m_fcKp0(ConfigurationManager::Get()->characterController_springConstantTorque),
									   m_fcDamp1(ConfigurationManager::Get()->characterController_dampingTorque),									
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
							     + m_fcDamp0 *  m_spAgentInfo->m_vVelocity);

	// compute external forces
	
	// we don't want the agent to go higher than maxHeight
	// so push him downwards with a force proportinal to its height
	float curHeight = m_pAgent->GetActor()->getGlobalPosition().y;
	float gain = -150.0f;
	float extraForceUp = curHeight > m_spAgentInfo->m_fcMaxHeight ? gain*(curHeight - m_spAgentInfo->m_fcMaxHeight) : 0.0f;
	
	// we also do not want the agent to go too low so add another force for that
	float minHeight = 150.0f;
	float extraForceDown = curHeight < minHeight? gain*(curHeight - minHeight) : 0.0f;

	// compute final force
	m_spAgentInfo->m_vForce += NxVec3(0.0f, extraForceUp + extraForceDown, 0.0f);

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

	// compute torque
	// get rotation matrix
	NxMat33 rotation = m_pAgent->GetActor()->getGlobalOrientation();
	// construct desired rotation matrix
	NxVec3 x = m_spAgentInfo->m_vDesiredVelocity;
	x.normalize();
	NxVec3 y(0.0, 1.0, 0.0);
	NxVec3 z = x.cross(y);
	z.normalize();
	NxMat33 desiredRot(x, y, z);
	desiredRot.setTransposed();
	rotation.setTransposed();
	// compute ΔR the rotation matrix that will
	// rotate the actor so that there is no error
	NxMat33 dr = desiredRot * rotation;
	// construct quaternion to get axis and angle from 
	// ΔR
	NxQuat q(dr);
	NxVec3 axis;
	float angle;
	q.getAngleAxis(angle, axis);
	// get global inertia tensor
	NxMat33 I = m_pAgent->GetActor()->getGlobalInertiaTensor();
	// get angular velocity
	NxVec3 w = m_pAgent->GetActor()->getAngularVelocity();
	// find torque
	m_spAgentInfo->m_vTorque =  I*(m_fcKp0 * axis * angle/RAD - m_fcDamp1*w) + w.cross(I*w);
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
