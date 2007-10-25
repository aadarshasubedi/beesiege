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
	m_spAgentInfo->m_vForce = m_fcKv0 * (m_fcDamp*m_spAgentInfo->m_vDesiredVelocity - m_spAgentInfo->m_vVelocity);
}
//-------------------------------------------------------------------------
void CharacterController::UpdatePhysX()
{
	
	if (!m_bTurnSpringsOff)
	{	
		m_pAgent->GetActor()->addForce(m_spAgentInfo->m_vForce, NX_FORCE);
	
		NxVec3 axis = NxVec3(0.0, 0.0, 1.0);
	
		NxMat33 rotation = m_pAgent->GetActor()->getGlobalOrientation();
		NxVec3 nxUp = rotation.getColumn(1);
		NiPoint3 up(nxUp.x, nxUp.y, nxUp.z);
		
		NxActor* queenActor = GameManager::Get()->GetQueen()->GetAgent()->GetActor();
		NxVec3 nxTarget = queenActor->getGlobalPosition();
		NiPoint3 target(nxTarget.x,nxTarget.y,nxTarget.z);
		NiPoint3 pos(m_spAgentInfo->m_vPos.x,m_spAgentInfo->m_vPos.y,m_spAgentInfo->m_vPos.z);
		NiMatrix3 newRotation = NiViewMath::LookAt(target, pos, up);
		NxMat33 nxNewRotation;
		NiPhysXTypes::NiMatrix3ToNxMat33(newRotation, nxNewRotation);
		m_pAgent->GetActor()->setGlobalOrientation(nxNewRotation);
		
	}
	
	
}
