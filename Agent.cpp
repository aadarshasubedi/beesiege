#include "Agent.h"
#include "CharacterController.h"
#include <NxActor.h>
#include <NiPoint3.h>
#include <NiMatrix3.h>
#include <NiViewMath.h>
#include <NiPhysX.h>
//-------------------------------------------------------------------------
Agent::Agent(NxActor* actor) : m_pActor(actor)
{
	m_spController = NiNew CharacterController(this);	
}
//-------------------------------------------------------------------------
Agent::~Agent()
{
	m_spController = 0;
}
//-------------------------------------------------------------------------
void Agent::Update(const NxVec3& target)
{
	m_spController->Update(target);
}
//-------------------------------------------------------------------------
void Agent::LookAt (const NxVec3& target)
{
	NxMat33 rotation = m_pActor->getGlobalOrientation();
	NxVec3 nxUp = rotation.getColumn(1);
	NiPoint3 up(nxUp.x, nxUp.y, nxUp.z);
	NiPoint3 NiTarget(target.x,target.y,target.z);
	NxVec3 pos = m_pActor->getGlobalPosition();
	NiPoint3 NiPos(pos.x, pos.y, pos.z);
	NiMatrix3 newRotation = NiViewMath::LookAt(NiTarget, NiPos, up);

	NxMat33 nxNewRotation;
	NiPhysXTypes::NiMatrix3ToNxMat33(newRotation, nxNewRotation);
	
	NxVec3 z = nxNewRotation.getColumn(2);
	z.y = 0.0f;
	z.normalize();
	nxNewRotation.setColumn(2, z);
	
	m_pActor->setGlobalOrientation(nxNewRotation);
}
//-------------------------------------------------------------------------