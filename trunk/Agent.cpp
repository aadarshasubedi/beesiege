/**
 * An agent contains a PhysX actor and a CharacterController and 
 * it is used to control objects using the CharacterController 
 * class 
 */
#include "Agent.h"
#include "CharacterController.h"
#include <NxActor.h>
#include <NiPoint3.h>
#include <NiMatrix3.h>
#include <NiViewMath.h>
#include <NiPhysX.h>

//------------------------------------------------------------------------- 
/** 
 * Ctor
 * 
 * @param actor
 */
Agent::Agent(NxActor* actor) : m_pActor(actor)
{
	m_spController = NiNew CharacterController(this);	
}
//------------------------------------------------------------------------- 
/** 
 * Dtor
 * 
 */
Agent::~Agent()
{
	m_spController = 0;
}
//------------------------------------------------------------------------- 
/** 
 * Updates the agent's CharacterController
 * 
 * @param target
 */
void Agent::Update(const NxVec3& target)
{
	m_spController->Update(target);
}
//------------------------------------------------------------------------- 
/** 
 * Orients the agent's actor to look at a certain 3d point
 * 
 * @param target
 */
void Agent::LookAt (const NxVec3& target)
{
	// get the actor's current global orientation
	NxMat33 rotation = m_pActor->getGlobalOrientation();
	// get the local Y axis
	NxVec3 nxUp = rotation.getColumn(1);
	// convert it to a NiPoint3
	NiPoint3 up(nxUp.x, nxUp.y, nxUp.z);
	// convert the target to a NiPoint3
	NiPoint3 NiTarget(target.x,target.y,target.z);
	// get the actor's current global position
	NxVec3 pos = m_pActor->getGlobalPosition();
	// convert it to a NiPoint3
	NiPoint3 NiPos(pos.x, pos.y, pos.z);
	// get a rotation matrix that looks at a certain target
	NiMatrix3 newRotation = NiViewMath::LookAt(NiTarget, NiPos, up);
	// transform it to a NxMat33
	NxMat33 nxNewRotation;
	NiPhysXTypes::NiMatrix3ToNxMat33(newRotation, nxNewRotation);
	// get the local Z axis
	NxVec3 z = nxNewRotation.getColumn(2);
	// remove roll
	z.y = 0.0f;
	z.normalize();
	nxNewRotation.setColumn(2, z);
	// set the new orientation
	m_pActor->setGlobalOrientation(nxNewRotation);
}
//-------------------------------------------------------------------------